#ifndef _FITTER_H_
#define _FITTER_H_

#include <iostream>
#include <memory>
#include <vector>


static const int UNSELECTED = 0;
static const int INITED = 0;
static const int ERASED = 1;

class Frame;
class Block;

struct KeyMap {
    const char ESC = 0x1B;
    const char U = 0x75;
    const char UP = 0x77;
    const char LEFT = 0x61;
    const char DOWN = 0x73;
    const char RIGHT = 0x64;
    const char ENTER = 0x0D;
};

using point_t = struct point_t {
    int x;
    int y;
};

using p_with_v = struct p_with_v {
    int value;
    int state;
};

// 数独块
class Block {
    int counts;
    p_with_v *_numbers[9];
  public:
    Block() : counts(0) {};
    bool isValid() const;
    bool isFull() const;
    void push_back(p_with_v *point);
    void print() const;
};


class Key {
    Frame *view;
    point_t settedP;
    int preVal;
    int curVal;
  public:
    Key(Frame *pview) : view(pview) {};
    Key(Frame *pview, const point_t &point, int preValue, int curValue);
    Key(const Key &);
    ~Key(){};

    bool execute(int nInputValue);
    void undo();
    point_t getPoint() { return settedP; }
    int getPreValue() { return preVal; }
    int getCurValue() { return curVal; }
    void setPoint(const point_t &point) { settedP = point; }
    void setPreValue(int preValue) { preVal = preValue; }
    void setCurValue(int curValue) { curVal = curValue; }
};


// 画布
class Frame {

    KeyMap *keyMap = new KeyMap();
    int _max_column;
    point_t cur_point;
    Block rblock[9];
    Block cblock[9];
    Block ablock[3][3];
    p_with_v myMap[81];
    std::vector<Key> commander;
    void init();
    void setValue(const int);
    void setValue(const point_t &, const int);
    void printLine(int line_no = -1) const;

  public:
    Frame(int index = 3);
    virtual ~Frame();

    void show() const;
    bool setPointValue(const point_t &, const int);
    bool setCurValue(const int nCurValue, int &nLastValue);
    point_t getCurPoint() { return cur_point; }
    bool isComplete();
    void load(const char *filename);
    void play();
};



#endif