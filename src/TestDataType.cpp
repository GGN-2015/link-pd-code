#include <cassert>
#include <iostream>

#include "DataType.h"
using namespace std;

void testDataType() { /* 用于测试数据类型的序列化是否正确 */
    auto s = (Segment3d){(Point3d){1.1, 1.2, 1.3}, (Point3d){2.3, 2.4, 2.5}, 9, 10}.serialize();
    assert(s == "((1.100000,1.200000,1.300000),(2.300000,2.400000,2.500000),9,10)");
    cout << "    OK:" << s << endl;
}
