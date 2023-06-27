
#include <cassert>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <memory.h>
#include <unordered_map>
#include <vector>
#include "fitter.h"

Key::Key(Frame *pview, const point_t &point, int preValue, int curValue)
    : view(pview), settedP(point), preVal(preValue), curVal(curValue) {}

Key::Key(const Key &key)
    : view(key.view), settedP(key.settedP), preVal(key.preVal),
      curVal(key.curVal) {}

bool Key::execute(int nInputValue) {
    if (!view)
        return false;

    settedP = view->getCurPoint();
    return view->setCurValue(nInputValue, preVal);
}

void Key::undo() {
    if (view) {
        view->setPointValue(settedP, preVal);
    }
    return;
}

bool Block::isValid() const {
    for (int i = 0; i < counts - 1; ++i) {
        for (int j = i + 1; j < counts; ++j) {
            if (UNSELECTED == _numbers[i]->value ||
                UNSELECTED == _numbers[j]->value)
                continue;

            if (_numbers[i]->value == _numbers[j]->value)
                return false;
        }
    }

    return true;
}

bool Block::isFull() const {
    for (int i = 0; i < counts; ++i) {
        p_with_v *p_point_value = _numbers[i];
        if (nullptr == p_point_value || UNSELECTED == p_point_value->value)
            return 0;
    }
    return 1;
}

void Block::print() const {
    std::cout << "\u2503 ";
    for (int i = 0; i < counts; ++i) {
        auto number = *(_numbers[i]);
        if (0 == number.value)
            std::cout << ' ' << " \u2503 ";
        else {
            if (number.state == ERASED)
                std::cout << "\033[" << 1 << ";" << 91 << "m" << number.value
                          << "\033[" << 0 << "m"
                          << " \u2503 ";
            else
                std::cout << number.value << " \u2503 ";
        }
    }
    std::cout << "\n";
}

void Block::push_back(p_with_v *point) {
    _numbers[counts++] = point;
}

Frame::Frame(int index) : _max_column(index * index), cur_point({0, 0}) {
    init();
}

Frame::~Frame() {
    if (keyMap)
        delete keyMap;
}

void Frame::show() const {
    system("cls");
    printLine();

    for (int row = 0; row < _max_column; ++row) {
        Block block = rblock[row];
        block.print();
        printLine(row);
    }
}

void Frame::printLine(int line_no) const {
    for (int colunm = 0; colunm < 9; ++colunm)
        std::cout << "\u254B"
                  << "\u2501"
                  << ((cur_point.y == line_no && cur_point.x == colunm)
                          ? "^"
                          : "\u2501")
                  << "\u2501";
    std::cout << "\u254B"
              << "\n";
}

void Frame::init() {
    memset(myMap, UNSELECTED, sizeof myMap);
    // 所有列
    for (int col = 0; col < _max_column; ++col) {
        Block column_block;

        for (int row = 0; row < _max_column; ++row) {
            column_block.push_back(myMap + row * 9 + col);
        }
        cblock[col] = column_block;
    }
    // 所有行
    for (int row = 0; row < _max_column; ++row) {
        Block row_block;

        for (int col = 0; col < _max_column; ++col) {
            row_block.push_back(myMap + row * 9 + col);
        }
        rblock[row] = row_block;
    }
    // 所有九宫格
    for (int idx = 0; idx < _max_column; ++idx) {
        Block xy_block;

        int xy_begin = idx / 3 * 27 + idx % 3 * 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                xy_block.push_back(myMap + xy_begin + i * 9 + j);
            }
        }
        ablock[idx / 3][idx % 3] = xy_block;
    }

    return;
}

bool Frame::setCurValue(const int value, int &lastValue) {
    auto point = myMap[cur_point.x + cur_point.y * 9];
    if (point.state == ERASED) {
        lastValue = point.value;
        setValue(value);
        return true;
    } else
        return false;
}

void Frame::setValue(const int value) {
    auto p = cur_point;
    this->setValue(p, value);
}
void Frame::setValue(const point_t &p, const int value) {
    myMap[p.x + p.y * 9].value = value;
}


bool Frame::isComplete() {
    for (size_t i = 0; i < 81; ++i) {
        if (myMap[i].value == UNSELECTED)
            return false;
    }
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (!rblock[row].isValid() || !cblock[col].isValid() ||
                !ablock[row / 3][col / 3].isValid())
                return false;
        }
    }
    return true;
}



void Frame::play() {
    show();

    char key = '\0';
    while (1) {
        key = getch();
        if (key >= '0' && key <= '9') {
            Key comkeys(this);
            if (!comkeys.execute(key - '0')) {
                std::cout << "这个数字不可修改\n";
            } else {
                commander.push_back(
                    std::move(comkeys)); // XXX: move without move constructor
                show();
                continue;
            }
        }
        if (key == keyMap->ESC) {
            exit(0);
        } else if (key == keyMap->U) {
            if (commander.empty())
                std::cout << "已达到撤回上限\n";
            else {
                Key &comkeys = commander.back();
                comkeys.undo();
                commander.pop_back();
                show();
            }
        } else if (key == keyMap->LEFT) {
            cur_point.x = (cur_point.x - 1) < 0 ? 0 : cur_point.x - 1;
            show();
        } else if (key == keyMap->RIGHT) {
            cur_point.x = (cur_point.x + 1) > 8 ? 8 : cur_point.x + 1;
            show();
        } else if (key == keyMap->DOWN) {
            cur_point.y = (cur_point.y + 1) > 8 ? 8 : cur_point.y + 1;
            show();
        } else if (key == keyMap->UP) {
            cur_point.y = (cur_point.y - 1) < 0 ? 0 : cur_point.y - 1;
            show();
        } else if (key == keyMap->ENTER) {
            if (isComplete()) {
                std::cout << "数独求解成功\n";
                getchar();
                exit(0);
            } else {
                std::cout << "数独求解失败\n";
            }
        }
    }
}

bool Frame::setPointValue(const point_t &stPoint, const int nValue) {
    auto point = myMap[stPoint.x + stPoint.y * 9];
    if (ERASED == point.state) {
        cur_point = stPoint;
        setValue(nValue);
        return 1;
    } else {
        return 0;
    }
}
void Frame::load(const char *filename) {
    std::fstream fs;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    for (int i = 0; i < 81; i++) {
        int tmpState;
        char ch;
        fs >> ch;
        if (ch == '$') {
            tmpState = 1;
            myMap[i].value = 0;
        } else {
            tmpState = 0;
            myMap[i].value = ch - '0';
        }

        myMap[i].state = tmpState;
    }

    cur_point.x = 0;
    cur_point.y = 0;
}