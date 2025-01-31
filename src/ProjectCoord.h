// 给定一个三维空间中的点序列，尝试十个随机方向
// 检查这些方向是否是合法的，如果有合法的返回一个即可，如果都不合法，那就报错，我们认为图片中有重合的点
#pragma once

#include "DataType.h"
#include "RandomCoord3d.h"

extern const int MAX_TRY_CNT; // default = 10

class ProjectCoord {
public:
    ProjectCoord(std::mt19937& gen, const Point3dList& p3dl);

    bool test() const; // 检测是否能够找到合法的投影方向
    Coord3d getOneCoord3d() const;

private:
    void init(std::mt19937& gen, int max_try_time=MAX_TRY_CNT); // 初始化程序
    bool checkBasisAvailable(const Coord3d& coord) const;

    Point3dList m_p3dl;
    bool available;         // 是否能找到合法的投影方向
    Coord3d coordAvailable; // 记录一个合法的坐标
};