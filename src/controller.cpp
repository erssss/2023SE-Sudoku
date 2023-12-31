// Copyright 2023 SE zjy&cry

#include <cstring>
#include "../include/controller.h"
#include "../include/generator.h"
#include "../include/solver.h"

FILE *puzzle_fp = NULL;
FILE *generator_fp = NULL;
FILE *solution_fp = NULL;

int test_input_flag = 0;

using std::cout;
using std::string;
using std::__cxx11::stoi;

bool create_sudoku(string path, bool is_puzzle, bool is_unique,
                   int hole_num_min, int hole_num_max, int hardness,
                   int counts) {
    Generator board(path, hole_num_min, hole_num_max, hardness, counts,
                    is_unique);
    // std::cout<<"hardness = "<<board.hardness<<"\n";
    board.Create(is_puzzle);
    if (!is_puzzle) {
        board.Output();
    }
    // printSudokuBoard(SIZE-1,board.getChessboard());
    if (is_puzzle)
        std::cout << "[成功]数独谜题生成成功\n";
    else
        std::cout << "[成功]数独终局生成成功\n";
    return 1;
}

bool solve_sudoku(string path, int counts) {
    std::cout << "input_path = " << path << "\n";
    for (int i = 0; i < counts; i++) {
        Puzzle puzzle;
        int lineno = i * SIZE;
        if (!puzzle.Read(path, lineno)) {
            std::cout << ("[错误]求解数独文件路径不合法\n");
            return 0;
        }
        puzzle.InitBoard();
        puzzle.Output(path);
        std::cout << "[成功]数独求解成功 " << i + 1 << "/" << counts << "\n";
    }
    return 1;
}

void printSudokuBoard(int x, char board[SIZE][SIZE]) {
    // 输出带有边框的棋盘
    for (int i = 0; i < x + 2; i++) {
        for (int j = 0; j < x + 2; j++) {
            if (i == 0 || i == x + 1 || j == 0 || j == x + 1) {
                std::cout << "————";
            } else {
                std::cout << "| " << board[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}
