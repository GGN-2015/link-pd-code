// 用于生成随机的坐标系
// 并计算换坐标系后点的坐标
#pragma once

#include <random>
#include <DataType.h>

// 生成随机向量
Point3d randomVector(std::mt19937& gen);

// 生成随机坐标系
void generateRandomBasis(std::mt19937& gen, Coord3d& coord);

// 计算某个点在坐标系变换之后的心得坐标
Point3d getNewCoordForPoint3d(const Point3d& p, const Coord3d& c);
