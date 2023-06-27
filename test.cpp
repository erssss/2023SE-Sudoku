#include <iostream>
#include <fstream>
#include <cctype>

using std::cout;
using std::string;

int main() {
    std::ifstream file("sudoku.txt");  // 打开文件 example.txt

    if (!file) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
string line;
    std::getline(file, line);  // 读取文件的一行
	std::cout<<line<<"\n";
    file.seekg(0, std::ios::beg);  // 将文件指针定位到文件开头

	int board_size = line.length()/2+1;


    char ch;
    while (file >> std::noskipws >> ch) {
        if (!std::isspace(ch)) {
            std::cout << ch;  // 输出非空格字符
        }
    }

    file.close();  // 关闭文件

    return 0;
}
