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

int main(int argc, char **argv) {

    int ch;
    int type = 0;
	int counts = 0;
	bool is_puzzle = 0;
	bool is_unique = 0;
	int hole_num = 0;
	int hardness = 0;
	string path="";
	string c = "f:t:m:n:d:p:u:h";
	char charArray[16]; // 假设足够大以容纳字符串
	strcpy(charArray, c.c_str());
    while ((ch = getopt(argc, argv, charArray)) != -1) {
        switch (ch) {
        case 'f':
            path = optarg;
            break;
        case 't':
            type = atoll(optarg);
            break;
		case 'p':
			is_puzzle = 1;
            break;
		case 'u':
			is_unique = 1;
            break;
		case 'n':
			counts = atoll(optarg);
            break;
		case 'd':
			hole_num = atoll(optarg);
            break;
		case 'm':
			hardness = atoll(optarg);
            break;
        case 'h':
            std::cout<<"【操作提示】:\n";
            std::cout<<"\t-f | 文件路径\n";
            std::cout<<"\t-t | 创建数独/求解数独[0/1] \n";
            std::cout<<"\t-m | 创建数独难度\n";
            std::cout<<"\t-n | 创建数独数量\n";
            std::cout<<"\t-d | 数独填空数目\n";
            std::cout<<"\t-p | 创建数独谜题\n";
            std::cout<<"\t-u | 创建数独解唯一\n";
            std::cout<<"\t-h | 操作提示\n";
            return 0;
        default:
            break;
        }
    }
	if(is_puzzle){
        std::cout<<"puzzle!\n";
    }
	if(type==1)
		solve_sudoku(path);
	else if(type==0)
		create_sudoku(path,is_puzzle,is_unique,hole_num,hardness,counts);
	else{
		std::cout<<"请输入正确的类型！\n";
	}
    // work(type,input_path,is_puzzle);
    // work(argv);

    return 0;
}