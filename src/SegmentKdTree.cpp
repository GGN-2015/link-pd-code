#include <algorithm>
#include <cassert>
#include <SegmentKdTree.h>

SegmentKdTree::SegmentKdTree(const Segment2dList& s2dl) {
    assert(s2dl.size() >= 1);
    root = build(s2dl);
}

bool cmpx(Segment2d s1, Segment2d s2) {
    auto mid1 = (s1.pFrom + s1.pTo)*0.5;
    auto mid2 = (s2.pFrom + s2.pTo)*0.5;
    return mid1.x != mid2.x ? mid1.x < mid2.x : mid1.y < mid2.y;
}

bool cmpy(Segment2d s1, Segment2d s2) {
    auto mid1 = (s1.pFrom + s1.pTo)*0.5;
    auto mid2 = (s2.pFrom + s2.pTo)*0.5;
    return mid1.y != mid2.y ? mid1.y < mid2.y : mid1.x < mid2.x;
}

KdTreeNode* SegmentKdTree::build(const Segment2dList& s2dl, int depth) {
    assert(s2dl.size() >= 1);

    KdTreeNode* newNode = new KdTreeNode;
    newNode -> aabb  = s2dl[0].getAABB(); // 合并所有元素的 AABB
    for(int i = 1; i < s2dl.size(); i += 1) {
        newNode->aabb = newNode->aabb.merge(s2dl[i].getAABB());
    }

    if(s2dl.size() == 1) { // 叶子节点
        newNode -> ch[0] = newNode -> ch[1] = nullptr;
        newNode -> s2d   = new Segment2d(s2dl[0]);
    }else {
        newNode -> s2d = nullptr;
        auto cpy = s2dl;                        // 拷贝一个 vector
        auto cmp = (depth & 1 ? cmpy : cmpx);   // 比较函数
        std::sort(cpy.begin(), cpy.end(), cmp); // 重新排序

        int mid = (cpy.size() - 1) >> 1; // 左右分拣
        Segment2dList rpart;
        Segment2dList lpart;
        for(int i = 0; i < cpy.size(); i += 1) {
            if(i <= mid) {
                lpart.push_back(cpy[i]);
            }else {
                rpart.push_back(cpy[i]);
            }
        }

        newNode -> ch[0] = build(lpart, depth + 1); // 递归
        newNode -> ch[0] = build(rpart, depth + 1);
    }
    return newNode;
}