#include <cassert>
#include <iostream>
using namespace std;

#include "DataType.h"
#include "RandomCoord3d.h"

void testRandomCoord3d() {
    cout << "testRandomCoord3d" << endl;
    std::random_device rd; // 随机数生成器
    std::mt19937 gen(rd());

    Coord3d coord; // 生成一个随机坐标系
    generateRandomBasis(gen, coord);

    auto udv = abs(coord.u.dot(coord.v)); // 检查是否是合法的坐标系
    auto udw = abs(coord.u.dot(coord.w));
    auto vdw = abs(coord.v.dot(coord.w));
    assert(udv < EPS && udw < EPS && vdw < EPS);
    cout << "    OK:" << coord.serialize() << endl;

    auto ex = Point3d{1, 0, 0}; // 计算原坐标系在新坐标系下的坐标
    auto ey = Point3d{0, 1, 0};
    auto ez = Point3d{0, 0, 1};
    auto nex = getNewCoordForPoint3d(ex, coord);
    auto ney = getNewCoordForPoint3d(ey, coord);
    auto nez = getNewCoordForPoint3d(ez, coord);
    auto old_trans = Coord3d{nex, ney, nez};

    auto test_vec = randomVector(gen); // 生成用于测试的随机向量
    auto pnew     = getNewCoordForPoint3d(test_vec, coord);
    auto pback    = getNewCoordForPoint3d(pnew, old_trans);
    assert(test_vec.serialize() == pback.serialize());
    cout << "    OK:" << test_vec.serialize() << " " << pnew.serialize() << " " << pback.serialize() << endl;
}
