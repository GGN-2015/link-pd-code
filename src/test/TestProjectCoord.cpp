#include <cassert>
#include <iostream>

#include <test/TestUtils.h>
#include <ProjectCoord.h>
using namespace std;

void testProjectCoord() { /* 用于测试随机三维投影点方向算法 */
    Point3dList p3dl {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1}
    };

    std::random_device rd; // 随机数生成器
    std::mt19937 gen(rd());
    auto pc = ProjectCoord(gen, p3dl);
    assert(pc.test());
    cout << OK_FLAG << pc.getOneCoord3d().serialize() << endl;

    Point3dList p3dfl { // 这是一个不合法的例子，无法得到合法投影方向
        {1.1, 1.2, 1.3},
        {1.1, 1.2, 1.3}
    };
    auto pcf = ProjectCoord(gen, p3dfl);
    assert(!pcf.test());
    cout << OK_FLAG << " can not get coord" << endl;
}