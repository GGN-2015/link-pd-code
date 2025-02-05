// 用于计算两个线段是否有交点以及线段的交点是什么
#pragma once

#include "DataType.h"

class SegmentInteresect {
public:
    SegmentInteresect(const Segment2d& s1, const Segment2d& s2);
    bool exist() const;                                           // 检查是否存在交点
    void getIntersect(double& t1, double& t2, Point2d& pt) const; // 如果交点存在，则返回在两个线段上的参数，以及交点的位置

private:
    void init(const Segment2d& s1, const Segment2d& s2); // 初始化

    bool existIntersect;
    double t1, t2;
    Point2d pt;
};