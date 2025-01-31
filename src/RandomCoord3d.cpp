#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

#include "RandomCoord3d.h"

// 生成随机三维向量
Point3d randomVector(std::mt19937& gen) {
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    return {
        dis(gen),
        dis(gen),
        dis(gen)
    };
}

// 生成随机坐标系的三个单位向量
void generateRandomBasis(std::mt19937& gen, Coord3d& coord) {
    Point3d& u = coord.u;
    Point3d& v = coord.v;
    Point3d& w = coord.w;

    // 生成第一个随机向量并归一化
    u = randomVector(gen).normalize();

    // 生成第二个随机向量
    Point3d temp;
    do {
        temp = randomVector(gen);
    } while (std::abs(temp.dot(u)) > 0.99);  // 确保不共线

    // 计算与 u 正交的向量
    v = (temp - u * temp.dot(u)).normalize();

    // 计算第三个向量
    w = u.cross(v);
}

// 计算某个点在坐标系变换后的新的坐标
Point3d getNewCoordForPoint3d(const Point3d& p, const Coord3d& c) {
    auto x = p.dot(c.u);
    auto y = p.dot(c.v);
    auto z = p.dot(c.w);
    return Point3d{x, y, z};
}