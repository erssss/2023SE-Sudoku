
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
