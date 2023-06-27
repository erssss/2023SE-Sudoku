#ifndef __WORK_H_
#define __WORK_H_
#include "generator.h"
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

extern FILE *puzzle_fp;
extern FILE *generator_fp;

extern int test_input_flag; // 用于单元测试输入是否正确

void create_sudoku(string path, bool is_puzzle = 0, bool is_unique = 0,
                   int hole_num_min = 20, int hole_num_max = 50,
                   int hardness = 1, int counts = 1);
void solve_sudoku(string path, int counts = 1);
void printSudokuBoard(int x, char board[SIZE][SIZE]);
#endif //!__WORK_H_