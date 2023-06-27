#ifndef _FITTER_H_
#define _FITTER_H_

#include <iostream>
#include <memory>
#include <vector>


static const int UNSELECTED = 0;
static const int INITED = 0;
static const int ERASED = 1;


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

class Frame;
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


#endif