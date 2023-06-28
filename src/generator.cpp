// Copyright 2023 SE zjy&cry

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include "../include/solver.h"
#include "../include/generator.h"

int idx[] = {1, 4, 7};
extern FILE *puzzle_fp;
extern FILE *generator_fp;
auto now = std::chrono::high_resolution_clock::now();
auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
// 将随机数种子与时间相关联
std::mt19937 gen(static_cast<unsigned int>(timestamp));
// std::mt19937 gen(2013216);
std::uniform_int_distribution<> dis(0, 100);

void Generator::Output() {
    std::ofstream generator_file(path);  // 打开输出文件

    if (!generator_file) {
        std::cout << "无法打开文件\n";
        return;
    }

    generator_file.write(out, out_cnt);

    if (!generator_file) {
        std::cout << "输出数独终局失败\n";
    }

    delete[] out;
    generator_file.close();  // 关闭文件
}

void Generator::Getchessboard(int ord[], char firstrow[], bool is_puzzle) {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            chessboard[i][j] = firstrow[modle[i][ord[j - 1]] - 'a'];
        }
    }
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            out[out_cnt++] = chessboard[i][j];
            if (j == 9)
                out[out_cnt++] = '\n';
            else
                out[out_cnt++] = ' ';
        }
    }

    if (num) {
        out[out_cnt++] = '\n';
    }
    if (is_puzzle) {
        Getpuzzle();
    }
}

void Generator::Create(bool is_puzzle) {
    int size = 18 * 9 * num + num + 10;
    out = new char[size];

    char firstrow[SIZE] = {"912345678"};
    int ord[SIZE];
    do {
        if (Create_exchange(ord, firstrow, is_puzzle))
            break;
    } while (std::next_permutation(firstrow + 1, firstrow + 9));
}

bool Generator::Create_exchange(int ord[], char firstrow[], bool is_puzzle) {
    char per1[2][4] = {"123", "132"},
         per2[6][4] = {"456", "465", "546", "564", "645", "654"},
         per3[6][4] = {"789", "798", "879", "897", "978", "987"};
    for (int i = 0; i < 2; i++) {
        for (int ii = 0; ii < 3; ii++)
            ord[ii] = per1[i][ii] - '0';

        for (int j = 0; j < 6; j++) {
            for (int jj = 0; jj < 3; jj++)
                ord[jj + 3] = per2[j][jj] - '0';

            for (int k = 0; k < 6; k++) {
                for (int kk = 0; kk < 3; kk++)
                    ord[kk + 6] = per3[k][kk] - '0';

                num--;
                Getchessboard(ord, firstrow, is_puzzle);
                if (num == 0)
                    return true;
            }
        }
    }
    return false;
}

void Generator::Getpuzzle() {
    int empty[SIZE];
    char tmp_chessboard[SIZE][SIZE];
    int sum = 0;
    Puzzle puzzle;
    puzzle.load(tmp_chessboard);
    for (int i = 1; i <= 9; i++) {
        empty[i] = 0;
        for (int j = 1; j <= 9; j++) {
            tmp_chessboard[i][j] = chessboard[i][j];
        }
    }
    int hole_num = dis(gen) % hole_num_min + hole_num_max;

     // 随机生成每个3*3内空格数量
     // while (sum <= hole_num) {
     //     sum = 0;
     //     empty[1] = dis(gen) % 7 + 2;  // 随机生成2~8
     //     sum += empty[1];
     //     for (int i = 2; i <= 9; i++) {
     //         if (empty[i - 1] >= 5)  // 上一个空格过多，生成2~4
     //             empty[i] = dis(gen) % 3 + 2;
     //         else  // 上一个空格过少，生成5~8
     //             empty[i] = dis(gen) % 4 + 5;
     //         sum += empty[i];
     //     }
     // }

    if (hardness == 0) {
        hole_num = 20;
    } else if (hardness == 1) {
        hole_num = 35;
    } else if (hardness == 2) {
        hole_num = 55;
    }

    int block_sum = hole_num /9;

    for (int i = 1; i <= 9 ; i++) {
        empty[i] = block_sum;
        sum += empty[i];
    }

    for (int i = 1; i <= 9 && sum <= hole_num; i++) {
        empty[i] ++;
        sum ++;
    }

    // while (sum <= hole_num) {
    //     empty[1] += (dis(gen) % 2 + 1);
    //     sum += empty[1];
    //     for (int i = 1; i <= 9 && sum <= hole_num; i++) {
    //          // std::cout<<sum<<"<<<<\n";
    //         if (empty[i - 1] >= 5)
    //             empty[i] += (dis(gen) % 2);
    //         else
    //             empty[i] += (dis(gen) % 2 + 1);
    //         sum += empty[i];
    //     }
    // }

    while (sum > hole_num) {
        int idx = dis(gen) % 9 + 1;
        empty[idx]--;
        sum--;
    }
     // for(int i=0;i<9;i++)
     // std::cout<<empty[i+1]<<" ";
     // 在每个3*3内随机生成空格位置，置0
    int tmp, i, j;
    for (int k = 1; k <= 9; k++) {
        while (empty[k]) {
            tmp = dis(gen) % 9 + 1;
            i = idx[(k - 1) / 3] + (tmp - 1) / 3;
            j = idx[(k - 1) % 3] + (tmp - 1) % 3;
            if (tmp_chessboard[i][j]) {
                char ch = tmp_chessboard[i][j];
                tmp_chessboard[i][j] = '$';
                puzzle.load(tmp_chessboard);
                puzzle.InitBoard();

                if (is_unique && !puzzle.Solution()) {
                     // std::cout<<"unique check\n";
                    tmp_chessboard[i][j] = ch;
                    continue;
                }

                empty[k]--;
            }
        }
    }
    std::ofstream puzzle_file(path, std::ios::app);

     // 输出quzzle到文件
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            puzzle_file << tmp_chessboard[i][j];
            puzzle_file << (j == 9 ? '\n' : ' ');
        }
    }

    if (num)
        puzzle_file << "\n";

    puzzle_file.close();
}
