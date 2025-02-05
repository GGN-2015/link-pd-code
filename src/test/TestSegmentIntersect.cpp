#include <cassert>
#include <iostream>
#include <test/TestUtils.h>
#include <SegmentIntersect.h>
using namespace std;

void testSegmentIntersect() { /* 用于测试线段求交的正确性 */
    {
        Point2d p1{1, 1}, q1{10, 1};
        Point2d p2{1, 2}, q2{10, 2};
        Segment2d s1{p1, q1, 0, 0};
        Segment2d s2{p2, q2, 0, 0};

        auto si = SegmentInteresect(s1, s2);
        assert(!si.exist());
        cout << OK_FLAG << s1.serialize() << s2.serialize() << "(no crossing)" << endl;
    }
    {
        Point2d p1{1, 1}, q1{2, 2};
        Point2d p2{1, 2}, q2{2, 1};
        Segment2d s1{p1, q1, 0, 0};
        Segment2d s2{p2, q2, 0, 0};

        auto si = SegmentInteresect(s1, s2);
        assert(si.exist());

        double t1, t2; Point2d pt;
        si.getIntersect(t1, t2, pt);
        assert(abs(t1 - 0.5) < EPS);
        assert(abs(t2 - 0.5) < EPS);
        cout << OK_FLAG << s1.serialize() << s2.serialize() << "(" << t1 << "," << t2 << ")" << endl;
    }
    {
        Point2d p1{0, 0}, q1{2, 2};
        Point2d p2{0, 2}, q2{1, 0};
        Segment2d s1{p1, q1, 0, 0};
        Segment2d s2{p2, q2, 0, 0};

        auto si = SegmentInteresect(s1, s2);
        assert(si.exist());

        double t1, t2; Point2d pt;
        si.getIntersect(t1, t2, pt);
        assert(abs(t1 - 1.0/3) < EPS);
        assert(abs(t2 - 2.0/3) < EPS);
        cout << OK_FLAG << s1.serialize() << s2.serialize() << "(" << t1 << "," << t2 << ")" << endl;
    }
    {
        Segment2d s3{{3, 5}, {5, 7}, 1, 0};
        Segment2d s4{{5, 7}, {7, 9}, 1, 1};

        auto si = SegmentInteresect(s3, s4);
        assert(si.getLinkedDetected());
        assert(!si.exist());
        cout << OK_FLAG << "linkedDetected" << endl;
    }
}