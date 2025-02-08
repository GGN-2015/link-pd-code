#include <cassert>
#include <iostream>

#include <test/TestUtils.h>
#include <DataType.h>
using namespace std;

void testDataType() { /* 用于测试数据类型的序列化是否正确 */
    {
        auto s = (Segment3d){(Point3d){1.1, 1.2, 1.3}, (Point3d){2.3, 2.4, 2.5}, 9, 10}.serialize();
        assert(s == "((1.100000,1.200000,1.300000),(2.300000,2.400000,2.500000),9,10)");
        cout << OK_FLAG << s << endl;
    }   
    {
        Segment2d s2d {
            {0, 2}, {5, 3}, 1, 7
        };
        auto s = s2d.getAABB().serialize();
        assert(s == "(0.000000,5.000000,2.000000,3.000000)");
        cout << OK_FLAG << s << endl;
    }
    {
        Segment3d s3d {
            {1.5, 2.0, 1.2},
            {3.5, 1.1, 4.3},
            1,
            8
        };
        auto pFrom = s3d.step(0.0);
        auto pTo   = s3d.step(1.0);
        auto pMove = s3d.step(2.0);
        assert(pFrom.serialize() == s3d.pFrom.serialize());
        assert(pTo.serialize()   == s3d.pTo.serialize());
        assert(pMove.serialize() == "(5.500000,0.200000,7.400000)");
        cout << OK_FLAG << s3d.serialize() << endl;
    }
    {
        Point2d p2d_1 { 1,  1};
        Point2d p2d_2 {-1,  1};
        Point2d p2d_3 {-1, -1};
        Point2d p2d_4 { 1, -1};
        assert(checkSame(p2d_1.calculatePolarAngle(),  45.0 / 180.0 * PI));
        assert(checkSame(p2d_2.calculatePolarAngle(), 135.0 / 180.0 * PI));
        assert(checkSame(p2d_3.calculatePolarAngle(), 225.0 / 180.0 * PI));
        assert(checkSame(p2d_4.calculatePolarAngle(), 315.0 / 180.0 * PI));
        cout << OK_FLAG << "calculatePolarAngle" << endl;
    }
    {
        Point3d p;
        FILE* fpin = fopen("./src/test/data/TestPoint3d.txt", "r");
        assert(fpin != nullptr);
        p.input(fpin);
        assert(p.serialize() == "(3.570000,2.640000,0.250000)");
        cout << OK_FLAG << p.serialize() << endl;
    }
}
