#include <iostream>

#include "NearestPoint.h"
#include "DataType.h"

#ifdef TEST_NEAREST_POINT

#include <cassert>
using namespace std;

int main() {
    cout << "-DTEST_NEAREST_POINT -DTEST\n";
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
    cout << "OK:" << s << endl;
    return 0;
}

#endif