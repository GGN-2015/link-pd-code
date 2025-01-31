// 修改自我自己 2023-03-23 写的平面最近点对
// 提交记录：https://www.luogu.com.cn/record/200874900
#pragma once

#include <algorithm>
#include <tuple>
#include <vector>
#include <limits>

#include "DataType.h"

class NearestPoint {
public:
    NearestPoint(const Point2dList& point2dList);

    // 计算最近点对
    double getMinDis() const;

private:
    static double sqr(double x) {
        return x * x;
    }
    static bool cmpx(const Point2d& A, const Point2d& B) {  // 按照 x 坐标进行排序 
        return A.x != B.x ? A.x < B.x : A.y < B.y; 
    }
    static double dis(Point2d i, Point2d j) { // 计算距离的平方
        return sqr(i.x - j.x) + sqr(i.y - j.y);
    }

    // 合并：归并排序
    void merge(int L, int mid, int R);

    // 求解
    double solve(int L, int R);

    Point2dList     ps, Ltmp, Rtmp;
    double          m_minDis;

    int lcnt, rcnt;
};