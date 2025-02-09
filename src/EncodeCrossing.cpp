#include <cassert>
#include <EncodeCrossing.h>
#include <SegmentIntersect.h>
using namespace std;
 
struct SortItem {
    std::string arc_name;
    double rad; // 算一个极角的相反数
};
bool sortItemCmp(const SortItem& s1, const SortItem& s2) { // 从正东开始逆时针排序
    return s1.rad < s2.rad;
}

std::string EncodeCrossing::getErr() const {
    return err;
}

EncodeCrossing::EncodeCrossing(const Segment3d& s3d_a, const Segment3d& s3d_b, std::string arc_a_in, std::string arc_a_out, std::string arc_b_in, std::string arc_b_out):
    s3d_a(s3d_a), s3d_b(s3d_b), arc_a_in(arc_a_in), arc_a_out(arc_a_out), arc_b_in(arc_b_in), arc_b_out(arc_b_out) {
    auto s2d_a = s3d_a.abandonZ();
    auto s2d_b = s3d_b.abandonZ();
    auto si = SegmentInteresect(s2d_a, s2d_b);
    
    if(!si.exist()) { // 线段交点必须存在，才可以求交点编码
        err = "intersection not exist";
        return;
    }

    double t1, t2; // 计算交叉点 rate
    Point2d pt;
    si.getIntersect(t1, t2, pt);

    auto pt1 = s3d_a.step(t1); // 计算三维空间中的交叉点
    auto pt2 = s3d_b.step(t2);

    if(pt1.abandonZ() != pt || pt2.abandonZ() != pt) {
        err = "intersection error";
        return;
    }

    if(fabs(pt1.z - pt2.z) <= EPS) {        // 两个 z 坐标必须可区分才可以
        err = "segments meet in 3d space"; // 我们希望两个线段在二维空间中有交点但是在三维空间中没有交点
        return;
    }

    // 假设我们在 z = +inf 位置向 z = -inf 方向看，离我们越远的点越靠下
    std::string begin_arc;
    if(pt1.z > pt2.z) { // 说明 pt1 更靠近我们
        begin_arc = arc_b_in;
    }else { // 说明 pt2 更靠近我们
        begin_arc = arc_a_in;
    }

    auto arr = std::vector<SortItem> { // 可以用与给所有对象按照极角排序
        {arc_a_in , -(s3d_a.pFrom.abandonZ() - pt).calculatePolarAngle()}, // 取相反数是为了从正东开始顺时针排序
        {arc_a_out, -(s3d_a.pTo  .abandonZ() - pt).calculatePolarAngle()},
        {arc_b_in , -(s3d_b.pFrom.abandonZ() - pt).calculatePolarAngle()},
        {arc_b_out, -(s3d_b.pTo  .abandonZ() - pt).calculatePolarAngle()},
    };
    sort(arr.begin(), arr.end(), sortItemCmp);

    int begin_pos = -1; // 寻找 begin_arc 出现的位置
    for(int i = 0; i < 4; i += 1) {
        if(arr[i].arc_name == begin_arc) {
            begin_pos = i;
            break;
        }
    }

    code = CrossingCode {
        arr[(begin_pos + 0) % 4].arc_name,
        arr[(begin_pos + 1) % 4].arc_name,
        arr[(begin_pos + 2) % 4].arc_name,
        arr[(begin_pos + 3) % 4].arc_name
    };
}

// 获取编码
CrossingCode EncodeCrossing::getCode() const {
    assert(err == ""); // 只有没发生错误才可以取答案
    return code;
}