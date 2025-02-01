// 所有用于测试的函数需要在此文件中进行注册
// -DTEST 可以打开测试开关，让主程序调用测试程序集合
#pragma once

void testDataType();
void testNearestPoint();
void testProjectCoord();
void testRandomCoord3d();
void testSegmentIntersect();

static void testAll() {
    testDataType();
    testNearestPoint();
    testProjectCoord();
    testRandomCoord3d();
    testSegmentIntersect();
}