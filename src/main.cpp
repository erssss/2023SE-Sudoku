#include "work.h"
#include <iomanip>
using namespace std;

char *optarg = NULL;
int optind = 1;
int opterr = 1;
#define _next_char(string) (char)(*(string + 1))

int getopt(int argc, char *argv[], char *opstring) {
    static char *pIndexPosition = NULL;
    char *pArgString = NULL;
    char *pOptString;

    if (pIndexPosition != NULL) {
        if (*(++pIndexPosition)) {
            pArgString = pIndexPosition;
        }
    }

    if (pArgString == NULL) {
        if (optind >= argc) {
            pIndexPosition = NULL;
            return EOF;
        }

        pArgString = argv[optind++];

        if (('/' != *pArgString) && ('-' != *pArgString)) {
            --optind;
            optarg = NULL;
            pIndexPosition = NULL;
            return EOF;
        }

        if ((strcmp(pArgString, "-") == 0) || (strcmp(pArgString, "--") == 0)) {
            optarg = NULL;
            pIndexPosition = NULL;
            return EOF;
        }
        pArgString++;
    }

    if (':' == *pArgString) {
        return (opterr ? (int)'?' : (int)':');
    } else if ((pOptString = strchr(opstring, *pArgString)) == 0) {
        optarg = NULL;
        pIndexPosition = NULL;
        return (opterr ? (int)'?' : (int)*pArgString);
    } else {
        if (':' == _next_char(pOptString)) {
            if ('\0' != _next_char(pArgString)) {
                optarg = &pArgString[1];
            } else {
                if (optind < argc)
                    optarg = argv[optind++];
                else {
                    optarg = NULL;
                    return (opterr ? (int)'?' : (int)*pArgString);
                }
            }
            pIndexPosition = NULL;
        } else {
            optarg = NULL;
            pIndexPosition = pArgString;
        }
        return (int)*pArgString;
    }
}

int type = 0;
int counts = 1;
bool is_puzzle = 0;
bool is_unique = 0;
int hole_num_min = 20;
int hole_num_max = 50;
int hardness = -1;
string path = "";
string arg = "";
bool processArgs(int argc, char *argv[]) {
    arg = argv[1];
    if (arg == "-s") {
        if (argc == 3) {
            path = argv[2];
            solve_sudoku(path, 1);
            return 1;
        } else if (argc == 5 && strcmp(argv[3], "-n") == 0) {
            counts = stoi(argv[4]);
            solve_sudoku(argv[2], counts);
            return 1;
        } else {
            std::cout << "[错误]请按照正确的格式输入文件路径: -s <path>\n";
            return 0;
        }
    } else if (arg == "-c") {
        if (argc == 3) {
            counts = stoi(argv[2]);
            if (counts > 1000000 || counts < 1) {
                std::cout << "[错误]请输入正确的数量，范围是1~1000000\n";
                return 0;
            } else {
                path = "sudoku_end.txt";
                create_sudoku(path, is_puzzle, counts = counts);
                return 1;
            }
        } else {
            std::cout << "[错误]请按照正确的格式输入: -c <counts>\n";
            return 0;
        }
    } else {
        for (int i = 1; i < argc; i++) {
            arg = argv[i];
            if (arg == "-n") {
                if (i + 1 >= argc) {
                    std::cout << "[错误]请按照正确的格式输入: -c <counts>\n";
                    return 0;
                }
                counts = stoi(argv[++i]);
                if (counts >= 10000 || counts < 1) {
                    std::cout << "[错误]请输入正确的数量，范围是1~10000\n";
                    return 0;
                }
            } else if (arg == "-m") {
                if (i + 1 >= argc) {
                    std::cout << "[错误]请按照正确的格式输入: -c <counts> -m "
                                 "<hardness>\n";
                    return 0;
                }
                hardness = stoi(argv[++i]);
                if (hardness < 1 || hardness > 3) {
                    std::cout << "[错误]请输入正确的难度，范围是1~3\n";
                    return 0;
                }
            } else if (arg == "-r") {
                if (i + 1 >= argc) {
                    std::cout
                        << "[错误]请按照正确的格式输入: -c <counts> -m "
                           "<hardness> -r <hole_num_min ~ hole_num_max> \n";
                    return 0;
                }
                std::string range = argv[i];
                size_t rangePos = range.find("~");
                if (rangePos == string::npos) {
                    std::cout
                        << "[错误]请按照正确的格式输入: -c <counts> -m "
                           "<hardness> -r <hole_num_min ~ hole_num_max> \n";
                    return 0;
                }
                hole_num_min = stoi(range.substr(0, rangePos));
                hole_num_max = stoi(range.substr(rangePos + 1));
                if (!(hole_num_max <= 55 && hole_num_max >= 20) ||
                    !(hole_num_min <= 55 && hole_num_min >= 20) ||
                    hole_num_min > hole_num_max) {
                    std::cout << "[错误]请输入正确的数目，范围是20~55\n";
                    return 0;
                }
            } else if (arg == "-u") {
                is_unique = 1;
            } else {
                std::cout << "[错误] " << argv[1]
                          << " 不存在，请输入正确的参数\n";
                return 0;
            }
        }
        is_puzzle = 1;
        create_sudoku(path, is_puzzle, is_unique, hole_num_min, hole_num_max,
                      hardness, counts);
        return 1;
    }
}

int main(int argc, char **argv) {

    // ******************* 雨课堂改版控制台参数 *******************

    processArgs(argc, argv);

    // ******************* 原版控制台参数 *******************
    // int ch;
    // int type = 0;
    // int counts = 1;
    // bool is_puzzle = 0;
    // bool is_unique = 0;
    // int hole_num_min = 20;
    // int hole_num_max = 50;
    // int hardness = -1;
    // string path = "";
    // string c = "f:t:m:n:d:x:u:h";
    // char charArray[16];
    // strcpy(charArray, c.c_str());
    // std::srand(std::time(nullptr));

    // while ((ch = getopt(argc, argv, charArray)) != -1) {
    //     switch (ch) {
    //     case 'f':
    //         path = optarg;
    //         break;
    //     case 't':
    //         type = atoll(optarg);
    //         break;
    //         // case 'p':
    //         // 	is_puzzle = 1;
    //         //     break;
    //     case 'u':
    //         is_unique = 1;
    //         break;
    //     case 'n':
    //         std::cout<<atoll(optarg)<<"\n";
    //         counts = atoll(optarg);
    //         break;
    //     case 'd':
    //         hole_num_min = atoll(optarg);
    //         break;
    //     case 'x':
    //         hole_num_max = atoll(optarg);
    //         break;
    //     case 'm':
    //         hardness = atoll(optarg);
    //         break;
    //     case 'h':
    //         std::cout << "【操作提示】:\n";
    //         std::cout << "\t-f | 文件路径\n";
    //         std::cout << "\t-t | 创建数独终局/创建数独谜题/求解数独[0/1/2]
    //         \n"; std::cout << "\t-m | 创建数独难度\n"; std::cout << "\t-n |
    //         创建数独数量\n"; std::cout << "\t-d | 数独填空数目区间\n";
    //         std::cout << "\t-u | 创建数独解唯一\n";
    //         std::cout << "\t-h | 操作提示\n";
    //         return 0;
    //     default:
    //         break;
    //     }
    // }

    // if (hardness!=-1&&(hardness > 2 || hardness < 0)) {
    //     std::cout << "请输入正确的难度！\n";
    //     return 1;
    // }

    // if (is_puzzle) {
    //     std::cout << "puzzle!\n";
    // }

    // if (type == 2)
    //     solve_sudoku(path);
    // else if (type == 1) {
    //     is_puzzle = 1;
    //     std::cout << "is unique = " << is_unique << "\n";
    //     create_sudoku(path, is_puzzle, is_unique, hole_num_min, hole_num_max,
    //                   hardness, counts);
    // } else if (type == 0)
    //     create_sudoku(path, is_puzzle, counts = counts);
    // else {
    //     std::cout << "请输入正确的类型！\n";
    // }
    // work(type,input_path,is_puzzle);
    // work(argv);

    return 0;
}