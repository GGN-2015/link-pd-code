#include <cassert>
#include <iostream>
#include <test/TestUtils.h>
#include <SegmentKdTree.h>
using namespace std;

void testSegmentKdTree() { /* 检测建树的基本功能 */
    { // 测试 has_serialize 类是否能正常工作
        auto v = has_serialize<int>::value;
        assert(v == false);
        auto u = has_serialize<SegmentKdTree>::value;
        assert(u == true);
        cout << OK_FLAG << "has_serialize" << endl;
    }
    {
        SegmentKdTree skdt({
            {{0, 0}, {0, 1}, 0, 0},
            {{0, 1}, {1, 1}, 0, 1},
            {{1, 1}, {0.5, 0}, 0, 2}
        });
        auto s = skdt.serialize();
        assert(s == "(ch0:(ch0:(ch0:NULL,ch1:NULL,aabb:(0.000000,0.000000,0.000000,1.000000),s2d:((0.000000,0.000000),(0.000000,1.000000),0,0)),ch1:(ch0:NULL,ch1:NULL,aabb:(0.000000,1.000000,1.000000,1.000000),s2d:((0.000000,1.000000),(1.000000,1.000000),0,1)),aabb:(0.000000,1.000000,0.000000,1.000000),s2d:NULL),ch1:(ch0:NULL,ch1:NULL,aabb:(0.500000,1.000000,0.000000,1.000000),s2d:((1.000000,1.000000),(0.500000,0.000000),0,2)),aabb:(0.000000,1.000000,0.000000,1.000000),s2d:NULL)");
        cout << OK_FLAG << s << endl;
    }
    {
        SegmentKdTree skdt({
            {{0, 1}, {0, 0}, 0, 0},
            {{0, 0}, {0.7, 0}, 0, 1},
            {{0.7, 0}, {0.5, 1}, 0, 2}
        });
        auto s = skdt.serialize();
        assert(s == "(ch0:(ch0:(ch0:NULL,ch1:NULL,aabb:(0.000000,0.700000,0.000000,0.000000),s2d:((0.000000,0.000000),(0.700000,0.000000),0,1)),ch1:(ch0:NULL,ch1:NULL,aabb:(0.000000,0.000000,0.000000,1.000000),s2d:((0.000000,1.000000),(0.000000,0.000000),0,0)),aabb:(0.000000,0.700000,0.000000,1.000000),s2d:NULL),ch1:(ch0:NULL,ch1:NULL,aabb:(0.500000,0.700000,0.000000,1.000000),s2d:((0.700000,0.000000),(0.500000,1.000000),0,2)),aabb:(0.000000,0.700000,0.000000,1.000000),s2d:NULL)");
        cout << OK_FLAG << s << endl;

        Segment2d s2d {
            {-1, 0}, {1, 1}, 1, 0
        };
        auto cs = skdt.getAllIntersect(s2d);
        assert(cs.size() == 2);
        auto crs_s = Serialize(cs);
        assert(crs_s == "[(0,0,0.500000),(0,2,0.772727)]");
        cout << OK_FLAG << crs_s << endl;
    }
    {
        SegmentKdTree skdt({
            {{0, 0}, {0, 1}, 1, 0},
            {{0, 1}, {0.5, 0}, 1, 1},
            {{0.5, 0}, {1, 1}, 1, 2},
            {{1, 1}, {1, 0}, 1, 3},
            {{1, 0}, {0, 0}, 1, 4},
        });

        Segment2d s2d1 {
            {-0.5, 0}, {1.5, 1}, 2, 0
        };

        auto cs1 = skdt.getAllIntersect(s2d1);
        assert(cs1.size() == 4);
        auto crs_s1 = Serialize(cs1);
        assert(crs_s1 == "[(1,0,0.250000),(1,1,0.600000),(1,2,0.666667),(1,3,0.250000)]");
        cout << OK_FLAG << crs_s1 << endl;

        Segment2d s2d2 {
            {0.5, 1}, {1.5, 0}, 3, 0
        };

        auto cs2 = skdt.getAllIntersect(s2d2);
        assert(cs2.size() == 2);
        auto crs_s2 = Serialize(cs2);
        assert(crs_s2 == "[(1,2,0.666667),(1,3,0.500000)]");
        cout << OK_FLAG << crs_s2 << endl;
    }
}
