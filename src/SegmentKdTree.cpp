#include <algorithm>
#include <cassert>
#include <SegmentKdTree.h>

SegmentKdTree::SegmentKdTree(const Segment2dList& s2dl) {
    assert(s2dl.size() >= 1);
    this -> s2dl = s2dl;
    root = build(0, s2dl.size() - 1);
}

std::string SegmentKdTree::serialize() const {
    if(root == nullptr) {
        return "NULL";
    }else {
        return root -> serialize();
    }
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

KdTreeNode* SegmentKdTree::build(int l, int r, int depth) { // Nlog^2N （实际上使用归并排序能做到 NlogN 但是我懒）
    assert(l <= r);

    KdTreeNode* newNode = new KdTreeNode;
    newNode -> aabb  = s2dl[l].getAABB(); // 合并所有元素的 AABB
    for(int i = l+1; i <= r; i += 1) {
        newNode->aabb = newNode->aabb.merge(s2dl[i].getAABB());
    }

    if(l == r) { // 叶子节点
        newNode -> ch[0] = newNode -> ch[1] = nullptr;
        newNode -> s2d   = new Segment2d(s2dl[l]);
    }else {
        newNode -> s2d = nullptr;
        auto cmp = (depth & 1 ? cmpy : cmpx);
        std::sort(s2dl.begin() + l, s2dl.begin() + r + 1, cmp); // 重新排序

        int mid = (l + r) >> 1; // 左右分拣
        newNode -> ch[0] = build(l,   mid, depth + 1); // 递归
        newNode -> ch[1] = build(mid+1, r, depth + 1);
    }
    return newNode;
}