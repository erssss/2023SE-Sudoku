#include "work.h"
#include "generator.h"
#include "solution.h"
#include <cstring>

FILE *puzzle_fp = NULL;
FILE *generator_fp = NULL;
FILE *solution_fp = NULL;

int test_input_flag = 0;

using namespace std;


void create_sudoku(string path, bool is_puzzle, bool is_unique,
                   int hole_num_min, int hole_num_max, int hardness,
                   int counts) {
    // if (counts > 0 && counts <= 100000) {
    // test_input_flag = 5;
    Generator board(path, hole_num_min, hole_num_max, hardness, counts,
                    is_unique);
    // std::cout<<"hardness = "<<board.hardness<<"\n";
    board.Create(is_puzzle);
    if (!is_puzzle)
        board.Output();
        // printSudokuBoard(SIZE-1,board.getChessboard());
    if (is_puzzle)
        std::cout << "[成功]数独谜题生成成功\n";
    else
        std::cout << "[成功]数独终局生成成功\n";

    // } else {
    //     test_input_flag = 4; // 终局数量越界
    //     std::cout << ("请输入正确的数量，范围是1~100000\n");
    // }
}

void solve_sudoku(string path, int counts) {
    // if (path == "") {
    //     test_input_flag = 6; // 没有输入求解数独文件路径
    //     std::cout << ("请输入数独文件\n");
    //     return;
    // }

    std::cout << "input_path = " << path << "\n";
    Puzzle puzzle;
    if (!puzzle.Read(path)) {
        std::cout << ("[错误]求解数独文件路径不合法\n");
        test_input_flag = 7; // 求解数独文件路径不合法
        return;
    }
    puzzle.InitBoard();
    puzzle.Output(path);
    fclose(solution_fp);
    std::cout << "[成功]数独求解成功\n";
    test_input_flag = 8; // 求解数独命令合法
}

void printSudokuBoard(int x, char board[SIZE][SIZE]) {
    // 输出带有边框的棋盘
    for (int i = 0; i < x + 2; i++) {
        for (int j = 0; j < x + 2; j++) {
            if (i == 0 || i == x + 1 || j == 0 || j == x + 1) {
                std::cout << "-- ";
            } else {
                std::cout << "| " << board[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}