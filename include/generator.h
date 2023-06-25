#ifndef __GENERATOR_H__
#define __GENERATOR_H__
#include <cstring>
#include <string>

using namespace std;
#define SIZE 10

class Generator {
  private:
    char chessboard[SIZE][SIZE]; // 数独终局盘
    char *out;
    int out_cnt;
    int num; // 数独终局数量
    // 数独模板
    char modle[11][11] = {
        "0",          "0abcdefghi", "0defghiabc", "0ghiabcdef", "0bcaefdhig",
        "0efdhigbca", "0higbcaefd", "0cabfdeigh", "0fdeighcab", "0ighcabfde"};
    void Getchessboard(int ord[SIZE], char firstrow[SIZE],
                       bool is_puzzle); // 数独终局输出
    bool Create_exchange(int ord[SIZE], char firstrow[SIZE],
                         bool is_puzzle); // 数独终局列交换
    void Getpuzzle();                     // 生成含空格的puzzle
  public:
    void Create(bool is_puzzle);
    void Output();
    std::string path;
    int hardness;
    int hole_num;
	bool is_unique;
    Generator(int n = 0) : num(n), out_cnt(0) {
        memset(chessboard, 0, sizeof(chessboard));
        out = NULL;
    }
    Generator(string p, int hole_num = 30, int hardness = 0, int n = 0,bool is_unique=0)
        : num(n), hole_num(hole_num), hardness(hardness), out_cnt(0),is_unique(is_unique) {
        memset(chessboard, 0, sizeof(chessboard));
        out = NULL;
        path = p;
    }
};

#endif // !__GENERATOR_H__
