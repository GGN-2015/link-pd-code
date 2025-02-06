// 用于计算两个线段是否有交点以及线段的交点是什么
#pragma once

#include <DataType.h>

class SegmentInteresect {
public:
    SegmentInteresect(const Segment2d& s1, const Segment2d& s2);
    bool exist() const;                                           // 检查是否存在交点
    bool getLinkedDetected() const;                               // 是否检测到相邻线段
    void getIntersect(double& t1, double& t2, Point2d& pt) const; // 如果交点存在，则返回在两个线段上的参数，以及交点的位置

private:
    void init(const Segment2d& s1, const Segment2d& s2); // 初始化

    inline bool isBorder(double rate) const { // 判断交点是否在线段的端点
        assert(-EPS < rate && rate < 1 + EPS);
        return rate < EPS || rate > 1 - EPS;
    }

    bool existIntersect;
    bool linkedDetected; // 是否检测到相邻线段
    double t1, t2;
    Point2d pt;
};