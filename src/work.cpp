#include "work.h"
#include "generator.h"
#include "solution.h"


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

void create_sudoku(string path,bool is_puzzle,bool is_unique, 
					int hole_num,int hardness,int counts){

        if (counts <= 0 || counts >=100000) {
            test_input_flag = 5; // 生成终局命令合法
            // if ((puzzle_fp = fopen("puzzle.txt", "w+")) == NULL) {
            //	std::cout<<("创建puzzle.txt文件失败\n");
            //	return -1;
            // }

            if ((generator_fp = fopen("sudoku_end.txt", "w+")) == NULL) {
                std::cout << ("创建数独终局文件失败\n");
                return;
            }

            Generator board(counts);
            board.Create();
            board.Output();

            fclose(generator_fp);
            std::cout << ("数独终局生成成功\n");

            // fclose(puzzle_fp);
            // puzzle_fp = NULL;

        } else {
            test_input_flag = 4; // 终局数量越界
            std::cout << ("请输入正确的数独终局数量，范围是1≤N≤1000000\n");
        }

}


void solve_sudoku(string path){
        char *path = NULL;
        path = argv[2];
        if (path == NULL) {
            test_input_flag = 6; // 没有输入求解数独文件路径
            std::cout << ("请输入数独文件\n");
            return;
        }

        if ((solution_fp = fopen("sudoku_solution.txt", "w+")) == NULL) {
            std::cout << ("创建数独求解文件失败\n");
            return;
        }

        std::cout << "path = " << path << "\n";
        Puzzle puzzle;
        if (!puzzle.Read(path)) {
            std::cout << ("求解数独文件路径不合法\n");
            test_input_flag = 7; // 求解数独文件路径不合法
            return;
        }
        puzzle.InitBoard();
        puzzle.Output();

        fclose(solution_fp);
        std::cout << ("数独求解成功\n");
        test_input_flag = 8; // 求解数独命令合法

}

