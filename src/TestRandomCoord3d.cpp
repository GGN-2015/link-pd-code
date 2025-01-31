#include <cassert>
#include <iostream>
using namespace std;

#include "DataType.h"
#include "RandomCoord3d.h"

#ifdef TEST_RANDOM_COORD3D

int main() {
    cout << "-DTEST_RANDOM_COORD3D -DTEST\n";

    // 随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());

    Point3d u, v, w;
    generateRandomBasis(gen, u, v, w);

    const double EPS = 1e-7;

    auto udv = abs(u.dot(v));
    auto udw = abs(u.dot(w));
    auto vdw = abs(v.dot(w));
    assert(udv < EPS && udw < EPS && vdw < EPS);
    cout << "OK:" << u.serialize() << v.serialize() << w.serialize() << endl;

    return 0;
}

#endif