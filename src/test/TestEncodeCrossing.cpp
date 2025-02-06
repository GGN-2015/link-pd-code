#include <iostream>

#include <test/TestUtils.h>
#include <EncodeCrossing.h>
#include <DataType.h>

#include <cassert>
using namespace std;

void testEncodeCrossing() {
    {
        Segment3d s3d_a {{0, 0,  1}, {1, 1,  1}, 1, 0};
        Segment3d s3d_b {{1, 0, -1}, {0, 1, -1}, 2, 0};
        auto ec = EncodeCrossing(s3d_a, s3d_b, "a_in", "a_out", "b_in", "b_out");
        assert(ec.getErr() == ""); // 没有错误
        assert(ec.getCode().serialize() == "(b_in,a_in,b_out,a_out)");
        cout << OK_FLAG << s3d_a.serialize() << s3d_b.serialize() << endl;
    }
    {
        Segment3d s3d_a {{ 0, -1, 1}, {0, 1, 1}, 1, 0};
        Segment3d s3d_b {{-1,  0, 0}, {1, 0, 0}, 2, 0};
        auto ec = EncodeCrossing(s3d_a, s3d_b, "a_in", "a_out", "b_in", "b_out");
        assert(ec.getErr() == "");
        assert(ec.getCode().serialize() == "(b_in,a_out,b_out,a_in)");
        cout << OK_FLAG << s3d_a.serialize() << s3d_b.serialize() << endl;
    }
    {
        Segment3d s3d_a {{ 0, -1, 0}, {0, 1, 0}, 1, 0};
        Segment3d s3d_b {{-1,  0, 0}, {1, 0, 0}, 2, 0};
        auto ec = EncodeCrossing(s3d_a, s3d_b, "a_in", "a_out", "b_in", "b_out");
        assert(ec.getErr() != "");
        cout << OK_FLAG << "conflict" << endl;
    }
}