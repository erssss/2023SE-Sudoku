#ifndef __WORK_H_
#define __WORK_H_
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>

using namespace std;

extern FILE *puzzle_fp;
extern FILE *generator_fp;

/*
        test_input_flag
                1:输入只有-c，没有终局个数
                2:终局个数含有其他非数字字符
                3:输入终局个数大于1000000
                4:终局数量为0
                5:生成终局命令合法
                6:没有输入求解数独文件路径
                7:求解数独文件路径不合法
                8:求解数独命令合法
                9:命令参数有误
*/
extern int test_input_flag; // 用于单元测试输入是否正确

int str2int(char *s);
void create_sudoku(string path, bool is_puzzle=0, bool is_unique=0,
                   int hole_num_min=20, int hole_num_max=50, int hardness=1,
                   int counts=1);
void solve_sudoku(string path);

#endif //!__WORK_H_