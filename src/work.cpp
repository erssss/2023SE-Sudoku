#include "work.h"
#include "generator.h"
#include "solution.h"
#include <cstring>

FILE *puzzle_fp = NULL;
FILE *generator_fp = NULL;
FILE *solution_fp = NULL;

int test_input_flag = 0;

using namespace std;

// 判断输入数独数量大小n是否合法
int str2int(char *s) {
    int len = strlen(s);
    int x = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            x = x * 10 + s[i] - '0';
        } else {
            test_input_flag = 2; // 输入终局个数含有其他字符
            std::cout << ("请输入合法的数独终局个数\n");
            return -1;
        }
        if (x > 1000000) {
            test_input_flag = 3; // 输入终局个数大于1000000
            std::cout << ("输入数独终局个数过大\n");
            return -1;
        }
    }
    return x;
}

void create_sudoku(string path, bool is_puzzle, bool is_unique,
                   int hole_num_min, int hole_num_max, int hardness,
                   int counts) {
    if (counts > 0 && counts <= 100000) {
        test_input_flag = 5;
        Generator board(path, hole_num_min,hole_num_max, hardness, counts, is_unique);
        // std::cout<<"hardness = "<<board.hardness<<"\n";
        board.Create(is_puzzle);
        if (!is_puzzle)
            board.Output();
        if (is_puzzle)
            std::cout << "数独谜题生成成功\n";
        else
            std::cout << "数独终局生成成功\n";

    } else {
        test_input_flag = 4; // 终局数量越界
        std::cout << ("请输入正确的数量，范围是1~100000\n");
    }
}

void solve_sudoku(string path,int counts) {
    if (path == "") {
        test_input_flag = 6; // 没有输入求解数独文件路径
        std::cout << ("请输入数独文件\n");
        return;
    }

    std::cout << "input_path = " << path << "\n";
    Puzzle puzzle;
    if (!puzzle.Read(path)) {
        std::cout << ("求解数独文件路径不合法\n");
        test_input_flag = 7; // 求解数独文件路径不合法
        return;
    }
    puzzle.InitBoard();
    puzzle.Output(path);
    fclose(solution_fp);
    std::cout << ("数独求解成功\n");
    test_input_flag = 8; // 求解数独命令合法
}


void printSudokuBoard(int x,int board[SIZE][SIZE]) {
    // 输出带有边框的棋盘
    for (int i = 0; i < x + 2; i++) {
        for (int j = 0; j < x + 2; j++) {
            if (i == 0 || i == x + 1 || j == 0 || j == x + 1) {
                std::cout << "- ";
            } else {
                std::cout << "| " << board[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}