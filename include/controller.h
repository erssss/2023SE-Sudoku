// Copyright 2023 SE zjy&cry

#ifndef INCLUDE_CONTROLLER_H_
#define INCLUDE_CONTROLLER_H_
#include <cstdio>
#include <cstring>
#include <ctime>
#include <string>
#include <iostream>
#include "./generator.h"
using std::__cxx11::stoi;
using std::cout;
using std::string;

extern FILE *puzzle_fp;
extern FILE *generator_fp;

extern int test_input_flag;  // 用于单元测试输入是否正确

bool create_sudoku(string path, bool is_puzzle = 0, bool is_unique = 0,
                   int hole_num_min = 20, int hole_num_max = 50,
                   int hardness = 1, int counts = 1);
bool solve_sudoku(string path, int counts = 1);
void printSudokuBoard(int x, char board[SIZE][SIZE]);

#endif  // INCLUDE_CONTROLLER_H_
