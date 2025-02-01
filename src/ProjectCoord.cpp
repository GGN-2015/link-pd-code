#include <cassert>

#include <ProjectCoord.h>
#include <NearestPoint.h>

const int MAX_TRY_CNT = 10;

ProjectCoord::ProjectCoord(std::mt19937& gen, const Point3dList& p3dl) {
    m_p3dl = p3dl;
    init(gen); // 检查是否有合法的投影方向
}

bool ProjectCoord::test() const {
    return available;
}

Coord3d ProjectCoord::getOneCoord3d() const {
    assert(available);
    return coordAvailable;
}

// 检查：在当前投影面上，我们要求任意两个点都不能重合
// 空集和单点集合可以任意投影
bool ProjectCoord::checkBasisAvailable(const Coord3d& coord) const {
    Point2dList p2dl;
    for(const auto& p3d: m_p3dl) {
        auto np3d = getNewCoordForPoint3d(p3d, coord);
        p2dl.push_back(np3d.abandonZ());
    }
    if(p2dl.size() <= 1) {
        return true;
    }else {
        // 最近点对算法要求至少有两个点参与计算
        return NearestPoint(p2dl).getMinDis() > 10 * EPS;
    }
}

void ProjectCoord::init(std::mt19937& gen, int max_try_time) {
    available = false;
    Coord3d coord;
    for(int i = 1; i <= max_try_time; i += 1) {
        generateRandomBasis(gen, coord);
        if(checkBasisAvailable(coord)) {
            available = true;
            coordAvailable = coord;
            break;
        }
    }
}