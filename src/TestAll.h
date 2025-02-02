// 所有用于测试的函数需要在此文件中进行注册
// -DTEST 可以打开测试开关，让主程序调用测试程序集合
// 此代码由自动化程序 genTestAll.py 生成，不要试图修改这个文件
// 那些所有以 test 为前缀的返回值为 void 类型的没有参数函数都会被当作测试用函数被程序自动化整理过来
#pragma once
#include <iostream>

void testDataType();
void testNearestPoint();
void testProjectCoord();
void testRandomCoord3d();
void testSegmentIntersect();

static void testAll() {
    std::cout << "testDataType" << std::endl; testDataType();
    std::cout << "testNearestPoint" << std::endl; testNearestPoint();
    std::cout << "testProjectCoord" << std::endl; testProjectCoord();
    std::cout << "testRandomCoord3d" << std::endl; testRandomCoord3d();
    std::cout << "testSegmentIntersect" << std::endl; testSegmentIntersect();
}
