// Copyright 2023 SE zjy&cry

#include "../include/solver.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

using std::cout;
using std::string;
using std::__cxx11::stoi;

extern FILE *solution_fp;

bool Puzzle::Read(string path) {
    std::ifstream input_file(path);

    if (!input_file) {
        std::cerr << "[失败]读取文件失败\n";
        return 0;
    }
    string line;
    std::getline(input_file, line);
    input_file.seekg(0, std::ios::beg);  // 将文件指针定位到文件开头

    int board_size = line.length() / 2 + 1;
    read = new char[board_size * board_size];
    out = new char[board_size * board_size * 2];

    char ch;
    int cnt = 0;
    while (input_file >> std::noskipws >> ch) {
        if (!std::isspace(ch)) {
            read[cnt++] = ch;
             // std::cout << ch;   // 输出非空格字符
        }
    }
    input_file.close();
    return true;
}

bool Puzzle::load(char mat[SIZE][SIZE]) {
    read = new char[SIZE * SIZE];
    out = new char[SIZE * SIZE * 2];
    int cnt = 0;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            read[cnt++] = mat[i][j];
        }
    }

    return true;
}

void Puzzle::Init() {
    memset(column, 0, sizeof(column));
    memset(row, 0, sizeof(row));
    memset(sub, 0, sizeof(sub));
    que.makeEmpty();
    que.push(Node(0, 0, 0));
    empty_num = 0;
}

void Puzzle::PrintSolver() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            std::cout << puzzleboard[i][j];
            if (j == 9)
                std::cout << '\n';
            else
                std::cout << ' ';
        }
    }
}

void Puzzle::InitBoard() {
     // PrintBoard();
    int len = strlen(read);
    for (int ch = 0; ch < len;) {  // 依次读取每一个字符
        Init();
         // 读入一个数独
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++) {
                puzzleboard[i][j] = read[ch];

                int k = (i - 1) / 3 * 3 + (j - 1) / 3 + 1;
                if (puzzleboard[i][j] == '$') {
                    que.push(Node(i, j, k));
                    empty_num++;
                } else {
                    int shift = puzzleboard[i][j] - '0' - 1;
                    row[i] |= 1 << shift;
                    column[j] |= 1 << shift;
                    sub[k] |= 1 << shift;
                }

                ch++;
                 // while (!(read[ch] >= '0' && read[ch] <= '9') && ch < len)
                 //     ch++;
            }
        }
         // 求解当前数独
        Solution();
        GetBoard();
        if (ch < len)
            out[out_cnt++] = '\n';
    }
}

void Puzzle::GetBoard() {
    out_cnt = 0;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            out[out_cnt++] = puzzleboard[i][j];
            if (j == 9)
                out[out_cnt++] = '\n';
            else
                out[out_cnt++] = ' ';
        }
    }
}

void Puzzle::PrintBoard() {
    for (int i = 1; i <= 81; i++) {
        std::cout << read[i];
    }
}

void Puzzle::Output(string path) {
     // std::cout << "\nstart write " << out_cnt << "\n";
    PrintSolver();
     // PrintBoard();
    std::cout << "cnt = " << out_cnt << "\n";
    std::ofstream solution_file("solved_" + path);  // 打开文件以写入模式

    if (!solution_file) {
        std::cout << "[失败]创建数独求解文件失败\n";
        return;
    }
    solution_file.write(out, std::strlen(out));

    if (!solution_file) {
        std::cout << "[失败]输出数独解失败\n";
    }

    delete[] read;
    delete[] out;
    solution_file.close();
}

// 返回1的个数
int Num1(int x) {
    int cot = 0;
    while (x) {
        x &= (x - 1);
        cot++;
    }
    return cot;
}

// 得到0的位置
int getNum(int x) {
    int cot = 1;
    while (x & 1) {
        cot++;
        x >>= 1;
    }
    return cot;
}

bool Puzzle::dfs(int tmp, Node node[]) {
    if (!empty_num)
        return true;
    for (int i = 1; i <= node[tmp].maybe_num; i++) {
        int dig = node[tmp].maybe[i];
        int shift = dig - 1;

        if (!((sub[node[tmp].k] >> shift) & 1) &&
            !((row[node[tmp].r] >> shift) & 1) &&
            !((column[node[tmp].c] >> shift) & 1)) {
            puzzleboard[node[tmp].r][node[tmp].c] = dig + '0';
            column[node[tmp].c] |= 1 << shift;
            row[node[tmp].r] |= 1 << shift;
            sub[node[tmp].k] |= 1 << shift;
            empty_num--;

            if (dfs(tmp + 1, node))
                return true;
            puzzleboard[node[tmp].r][node[tmp].c] = '0';
            sub[node[tmp].k] ^= 1 << shift;
            row[node[tmp].r] ^= 1 << shift;
            column[node[tmp].c] ^= 1 << shift;
            empty_num++;
        }
    }
    return false;
}

bool Puzzle::Solution() {
    bool flag = true;
    bool unique = true;
    Node tmp(-1, -1, -1);
    while (empty_num) {
         // 填写唯一解空格
        while (!que.isEmpty()) {
            tmp = que.front();
            que.pop();

            if (tmp.k == 0) {  // 一轮标记
                if (flag) {
                    flag = false;
                    que.push(tmp);
                } else {
                    break;  // 无唯一确定方格
                }
            } else {
                int result = row[tmp.r] | column[tmp.c] | sub[tmp.k];
                if (Num1(result) == 8) {  // 找到一个唯一确定方格
                    int sure_num = getNum(result);
                    int shift = sure_num - 1;
                    puzzleboard[tmp.r][tmp.c] = sure_num + '0';
                    flag = true;
                    empty_num--;
                    column[tmp.c] |= 1 << shift;
                    row[tmp.r] |= 1 << shift;
                    sub[tmp.k] |= 1 << shift;
                } else {  // 重新加入队列
                    que.push(tmp);
                }
            }
        }

        if (!empty_num)
            break;
         // 求出所有非唯一解空格可填的数字，dfs求解
        unique = false;
        Node node[65];
        int cot = 0;
        while (!que.isEmpty()) {
            tmp = que.front();
            que.pop();
            if (!tmp.r)
                continue;
            int result = row[tmp.r] | column[tmp.c] | sub[tmp.k];
            for (int i = 1; i <= 9; i++) {
                if ((result & (1 << (i - 1))) == 0) {
                    tmp.maybe[++tmp.maybe_num] = i;
                }
            }

            node[++cot] = tmp;
        }
        std::sort(node + 1, node + cot + 1);
        if (!dfs(1, node)) {
             // std::cout << ("有不合法数独\n");
            return 0;
        }
    }
    return unique;
}
