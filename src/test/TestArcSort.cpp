#include <cassert>
#include <iostream>

#include <ArcSort.h>
#include <test/TestUtils.h>
using namespace std;

void testArcSort() {
    {
        auto as = ArcSort("000000", {make_pair(1, 0.4), make_pair(1, 0.6), make_pair(0, 0.7)});
        assert(as.serialize() == "(000000,[(0,0.700000),(1,0.400000),(1,0.600000)])");
        assert(as.getBeforeName(make_pair(0, 0.7)) == "c_000000#s_000000"); // component 0, segment 0
        assert(as.getAfterName (make_pair(0, 0.7)) == "c_000000#s_000001");
        assert(as.getBeforeName(make_pair(1, 0.4)) == "c_000000#s_000001");
        assert(as.getAfterName (make_pair(1, 0.4)) == "c_000000#s_000002");
        assert(as.getBeforeName(make_pair(1, 0.6)) == "c_000000#s_000002");
        assert(as.getAfterName (make_pair(1, 0.6)) == "c_000000#s_000000");
        cout << OK_FLAG << as.serialize() << endl;
    }
}