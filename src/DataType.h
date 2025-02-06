#pragma once

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

static const double EPS = 1e-5;
const double PI = std::acos(-1); // 定义 π 的值

// 保留六位小数
static std::string doubleToString(double value, int precision=6) { 
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

//包围盒
struct AABB {
    double minx, maxx, miny, maxy;

    AABB merge(const AABB& rhs) const { // 合并包围盒
        return {
            std::min(minx, rhs.minx),
            std::max(maxx, rhs.maxx),
            std::min(miny, rhs.miny),
            std::max(maxy, rhs.maxy)
        };
    }

    std::string serialize() const {
        return "("
            + doubleToString(minx) + ","
            + doubleToString(maxx) + ","
            + doubleToString(miny) + ","
            + doubleToString(maxy) + ")";
    }

    bool unlap(const AABB& rhs) const { // 包围盒不重叠的情况
        return 
            minx > rhs.maxx + EPS ||
            maxx < rhs.minx - EPS ||
            miny > rhs.maxy + EPS ||
            maxy < rhs.miny - EPS;
    }
};

// 描述二维空间中的点集合
struct Point2d {
    double x, y;
    inline std::string serialize() const {
        return "(" + doubleToString(x) + "," + doubleToString(y) + ")";
    }

    // 向量加法
    Point2d operator+(const Point2d& other) const {
        return {x + other.x, y + other.y};
    }

    // 向量减法
    Point2d operator-(const Point2d& other) const {
        return {x - other.x, y - other.y};
    }

    // 向量数乘
    Point2d operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }

    // 向量点积
    double dot(const Point2d& other) const {
        return x * other.x + y * other.y;
    }

    // 向量叉积
    double cross(const Point2d& other) const {
        return x * other.y - y * other.x;
    }

    // 向量模长
    double length() const {
        return std::sqrt(x * x + y * y);
    }

    // 向量归一化
    Point2d normalize() const {
        double len = length();
        if (len > 0) {
            return {x / len, y / len};
        }
        return {0, 0};
    }

    AABB getAABB() const { // 获得一个点的包围盒
        return {
            x, x, y, y
        };
    }


    // 计算极角的函数
    double calculatePolarAngle() {
        double angle = std::atan2(y, x); // 使用 atan2 函数计算极角，结果范围是 -π 到 π
        if (angle < 0) { // 如果角度为负，将其转换到 0 到 2π 的范围
            angle += 2 * PI;
        }
        return angle;
    }
};
typedef std::vector<Point2d> Point2dList;

// 描述三维空间中的点
struct Point3d {
    double x, y, z;
    Point2d abandonZ() const { // 丢弃 z 坐标
        return (Point2d){x, y};
    }
    inline std::string serialize() const {
        return "(" + doubleToString(x) + "," + doubleToString(y) + "," + doubleToString(z) + ")";
    }

    // 向量加法
    Point3d operator+(const Point3d& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    // 向量减法
    Point3d operator-(const Point3d& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    // 向量数乘
    Point3d operator*(double scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    // 向量点积
    double dot(const Point3d& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // 向量叉积
    Point3d cross(const Point3d& other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

    // 向量模长
    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // 向量归一化
    Point3d normalize() const {
        double len = length();
        if (len > 0) {
            return {x / len, y / len, z / len};
        }
        return {0, 0, 0};
    }
};
typedef std::vector<Point3d> Point3dList;

// 用于描述一个三维坐标系
struct Coord3d {
    Point3d u, v, w;
    inline std::string serialize() const {
        return "("
            + u.serialize() + ","
            + v.serialize() + ","
            + w.serialize() + ")";
    }
};

// 描述二维空间中的线段
struct Segment2d {
    Point2d pFrom, pTo;
    int component_id, segment_id;

    inline std::string serialize() const {
        return "("
            + pFrom.serialize() + ","
            + pTo.serialize() + ","
            + std::to_string(component_id) + ","
            + std::to_string(segment_id) + ")";
    }

    // 线段的两个端点不重合
    bool isSegment() const {
        return (pFrom - pTo).length() > EPS;
    }

    AABB getAABB() const {
        return pFrom.getAABB().merge(pTo.getAABB());
    }

    inline Point2d step(double rate) const { // 在线段上找一个点
        return pFrom + (pTo - pFrom) * rate;
    }
};

// 描述三维空间中的线段
struct Segment3d {
    Point3d pFrom, pTo;

    int component_id; // 描述线段所处的连通分支的编号
    int segment_id;   // 描述线段在连通分支内的编号（所有编号从零开始）

    inline std::string serialize() const {
        return "("
            + pFrom.serialize() + ","
            + pTo.serialize() + ","
            + std::to_string(component_id) + ","
            + std::to_string(segment_id) + ")";
    }

    inline Segment2d getSegment2d() const { // 抛弃 z 坐标
        return {
            pFrom.abandonZ(),
            pTo.abandonZ(),
            component_id,
            segment_id
        };
    }

    inline Point3d step(double rate) const { // 在线段上找一个点
        return pFrom + (pTo - pFrom) * rate;
    }
};

typedef std::vector<Segment2d> Segment2dList;

// 交叉点编码
typedef std::tuple<std::string, std::string, std::string, std::string> CrossingCode;