#include <cassert>
#include <iostream>
#include <SegmentIntersect.h>
using namespace std;

// 计算向量 pq 和 pr 的叉积，判断点 r 相对于线段 pq 的位置
int orientation(const Point2d& p, const Point2d& q, const Point2d& r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (abs(val) < EPS) return 0;  // 共线
    return (val > 0) ? 1 : 2; // 1 表示顺时针，2 表示逆时针
}

// 判断点 q 是否在线段 pr 上
bool onSegment(const Point2d& p, const Point2d& q, const Point2d& r) {
    return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
           q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
}


// 判断两条线段 p1q1 和 p2q2 是否相交
bool doIntersect(const Point2d& p1, const Point2d& q1, const Point2d& p2, const Point2d& q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // 一般情况
    if (o1 != o2 && o3 != o4) return true;

    // 特殊情况：共线且重叠
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

// 计算两条线段的交点
bool findIntersection(const Point2d& p1, const Point2d& q1, const Point2d& p2, const Point2d& q2, Point2d& intersection) {
    if (!doIntersect(p1, q1, p2, q2)) return false;

    double x1 = p1.x, y1 = p1.y;
    double x2 = q1.x, y2 = q1.y;
    double x3 = p2.x, y3 = p2.y;
    double x4 = q2.x, y4 = q2.y;

    double denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (abs(denominator) < EPS) { // 特殊处理线段平行的情况
        double p2_proj = (p2 - p1).dot(q1 - p1) / (q1 - p1).length() / (q1 - p1).length();
        double q2_proj = (q2 - p1).dot(q1 - p1) / (q1 - p1).length() / (q1 - p1).length();
        double vmin = std::min(p2_proj, q2_proj);
        double vmax = std::max(p2_proj, q2_proj);
        
        if(0 > vmax + EPS || 1 < vmin - EPS) return false; // 区间没有交集
        else {
            double lpos = std::max(vmin, 0.0);
            double rpos = std::min(1.0, vmax);
            double mpos = (lpos + rpos) / 2;
            intersection = (q1 - p1) * mpos + p1; // 以区间中点作为交点
            return true;
        }
    }

    intersection.x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denominator;
    intersection.y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denominator;

    return true;
}

SegmentInteresect::SegmentInteresect(const Segment2d& s1, const Segment2d& s2) {
    init(s1, s2);
}

bool SegmentInteresect::getLinkedDetected() const {
    return linkedDetected;
}

void SegmentInteresect::init(const Segment2d& s1, const Segment2d& s2) {
    assert(s1.isSegment());
    assert(s2.isSegment());

    existIntersect = findIntersection(s1.pFrom, s1.pTo, s2.pFrom, s2.pTo, pt);
    linkedDetected = false;
    if(existIntersect) {
        t1 = (pt - s1.pFrom).length() / (s1.pTo - s1.pFrom).length();
        t2 = (pt - s2.pFrom).length() / (s2.pTo - s2.pFrom).length();

        if(isBorder(t1) && isBorder(t2)) { //! 忽略所有在线段端点的交点，以避免相邻线段之间的影响
            existIntersect = false;
            linkedDetected = true;
        }
    }
}

void SegmentInteresect::getIntersect(double& t1, double& t2, Point2d& pt) const {
    assert(exist());
    t1 = this -> t1;
    t2 = this -> t2;
    pt = this -> pt;
}

bool SegmentInteresect::exist() const {
    return existIntersect;
}