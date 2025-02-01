#include <iostream>

#include "NearestPoint.h"
#include "DataType.h"

#include <cassert>
using namespace std;

void testNearestPoint() {
    cout << "testNearestPoint" << endl;
    Point2dList p2dl {
        {1, 1},
        {1, 9},
        {9, 1},
        {9, 9},
        {0, 10}
    };
    auto ans = NearestPoint(p2dl).getMinDis();
    auto s = doubleToString(ans); // 检查答案
    assert(s == "1.414214");
    cout << "    OK:" << s << endl;
}
