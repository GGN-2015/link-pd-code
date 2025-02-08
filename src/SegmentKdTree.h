// 把所有线段按照中点的位置构建 KD-Tree
// 根节点在 x 方向上划分，每个树节点记录 AABB 用于剪枝
#pragma once

#include <DataType.h>

struct KdTreeNode {
    KdTreeNode* ch[2];  // 记录左右儿子，叶子节点为 nullptr
    AABB aabb;          // 所有 Point2d 的 AABB
    Segment2d* s2d;     // 非叶子节点取 nullptr 即可

    std::string serialize() const {
        std::string ans = "(";
        for(int i = 0; i <= 1; i += 1) {
            ans += "ch" + std::to_string(i) + ":";
            if(ch[i]) {
                ans += ch[i] -> serialize();
            }else {
                ans += "NULL";
            }
            ans += ",";
        }
        ans += "aabb:";
        ans += aabb.serialize() + ",";
        ans += "s2d:";
        if(s2d) {
            ans += s2d -> serialize();
        }else {
            ans += "NULL";
        }
        return ans + ")";
    }

    void free() { // 释放所有内存空间
        for(int i = 0; i <= 1; i += 1) {
            if(ch[i] != nullptr) {
                ch[i] -> free();
                delete ch[i];
                ch[i] = nullptr;
            }
        }
        if(s2d != nullptr) { // 叶子节点记录的节点信息也需要删除
            delete s2d;
            s2d = nullptr;
        }
    }
};

struct IntersectionRecord {
    int component_id;
    int segment_id;
    double rate;

    std::string serialize() const {
        return "("
            + std::to_string(component_id) + ","
            + std::to_string(segment_id) + ","
            + doubleToString(rate) + ")";
    }
};

class SegmentKdTree {
public:
    SegmentKdTree(const Segment2dList& s2dl);
    ~SegmentKdTree(); // 释放所有内存

    std::vector<IntersectionRecord> 
        getAllIntersect(const Segment2d& s2d) const; // 给定一个线段，求所有线段与已知线段的交点位置
                                                     // 返回的类型是（component id, segment id, rate）
                                                     // 计算时需要注意跳过同一根线段以及相邻的线段

    std::string serialize() const;

private:
    KdTreeNode* build(int l, int r, int depth=0);
    void getAllIntersectIn(std::vector<IntersectionRecord>& ans, KdTreeNode* root, const Segment2d& s2d) const; // 获得某个节点中的所有交点
    void getIntersectForS2d(std::vector<IntersectionRecord>& ans, const Segment2d& s2d_a, const Segment2d& s2d_b) const; // 两个线段求教点，计算 s2d_a 上的交点信息

    Segment2dList s2dl;
    KdTreeNode* root;
};