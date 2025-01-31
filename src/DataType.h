#pragma once

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

// 保留六位小数
static std::string doubleToString(double value, int precision=6) { 
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

// 描述二维空间中的点集合
struct Point2d {
    double x, y;
    inline std::string serialize() const {
        return "(" + doubleToString(x) + "," + doubleToString(y) + ")";
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
};