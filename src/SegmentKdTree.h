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
            if(ch[i]) {
                ans += ch[i] -> serialize();
            }else {
                ans += "NULL";
            }
            ans += ",";
        }
        ans += aabb.serialize() + ",";
        if(s2d) {
            ans += s2d -> serialize();
        }else {
            ans += "NULL";
        }
        return ans + ")";
    }
};

class SegmentKdTree {
public:
    SegmentKdTree(const Segment2dList& s2dl);

    std::vector<std::tuple<int, int, double>> 
        getAllIntersect(const Segment2d& s2d) const; // 给定一个线段，求所有线段与已知线段的交点位置
                                                     // 返回的类型是（link id, segment id, rate）
                                                     // 计算时需要注意跳过同一根线段以及相邻的线段
private:
    KdTreeNode* build(const Segment2dList& s2dl, int depth=0);
    KdTreeNode* root;
};