#include <cassert>
#include <EncodeCrossing.h>
#include <SegmentIntersect.h>
 
struct SortItem {
    std::string arc_name;
    double rad; // 算一个极角的相反数
};

EncodeCrossing::EncodeCrossing(const Segment3d& s3d_a, const Segment3d& s3d_b, std::string arc_a_in, std::string arc_a_out, std::string arc_b_in, std::string arc_b_out) {
    auto s2d_a = s3d_a.getSegment2d();
    auto s2d_b = s3d_b.getSegment2d();
    auto si = SegmentInteresect(s2d_a, s2d_b);
    assert(si.exist()); // 线段交点必须存在，才可以求交点编码

    double t1, t2; // 计算交叉点 rate
    Point2d pt;
    si.getIntersect(t1, t2, pt);

    auto pt1 = s3d_a.step(t1); // 计算三维空间中的交叉点
    auto pt2 = s3d_b.step(t2);
    assert(pt1.abandonZ().serialize() == pt.serialize());
    assert(pt2.abandonZ().serialize() == pt.serialize());
    
    assert(abs(pt1.z - pt2.z) > EPS); // 两个 z 坐标必须可区分才可以

    // 假设我们在 z = +inf 位置向 z = -inf 方向看，离我们越远的点越靠下
    std::string begin_arc;
    if(pt1.z > pt2.z) { // 说明 pt1 更靠近我们
        begin_arc = arc_b_in;
    }else { // 说明 pt2 更靠近我们
        begin_arc = arc_a_in;
    }

    auto arr = std::vector<SortItem> { // 可以用与给所有对象按照极角排序
        {arc_a_in , -(s3d_a.pFrom.abandonZ() - pt).calculatePolarAngle()},
        {arc_a_out, -(s3d_a.pTo  .abandonZ() - pt).calculatePolarAngle()},
        {arc_b_in , -(s3d_b.pFrom.abandonZ() - pt).calculatePolarAngle()},
        {arc_b_out, -(s3d_b.pTo  .abandonZ() - pt).calculatePolarAngle()},
    };

    assert(false); // 没写完
}

// 获取编码
CrossingCode EncodeCrossing::getCode() const {
    return code;
}