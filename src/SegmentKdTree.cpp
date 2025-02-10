#include <algorithm>
#include <cassert>
#include <SegmentKdTree.h>
#include <SegmentIntersect.h>

#include <iostream>
using namespace std;

SegmentKdTree::SegmentKdTree(const Segment2dList& s2dl):dfs_cnt(0) {
    assert(s2dl.size() >= 1);
    this -> s2dl = s2dl;
    root = build(0, s2dl.size() - 1);
}

SegmentKdTree::~SegmentKdTree() { // 释放所有内存空间
    if(root != nullptr)
        root -> free();
    delete root;
    root = nullptr;
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
        newNode -> s2d   = new Segment2d(s2dl[l]); // 注意，此处我们使用了 new 拷贝了节点信息
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

// 计算所有可能的线段交点
std::vector<IntersectionRecord> SegmentKdTree::getAllIntersect(const Segment2d& s2d) {
    auto ans = std::vector<IntersectionRecord>{};
    getAllIntersectIn(ans, root, s2d);
    sort(ans.begin(), ans.end(), IrCmp);
    return ans;
}

// 求两个线段的交点
void SegmentKdTree::getIntersectForS2d(std::vector<IntersectionRecord>& ans, const Segment2d& s2d_a, const Segment2d& s2d_b) {
    auto si = SegmentInteresect(s2d_a, s2d_b);
    if(!si.exist()) { // 交点不存在
        return;
    }
    double t1, t2; // 求交点，得到交点位置以及参数
    Point2d pt;
    si.getIntersect(t1, t2, pt);
    auto new_crs = IntersectionRecord{
        s2d_a.component_id,
        s2d_a.segment_id,
        t1
    };
    ans.push_back(new_crs); // 把新的交点追加到列表中
}

// 获得某个节点中的所有交点
void SegmentKdTree::getAllIntersectIn(std::vector<IntersectionRecord>& ans, KdTreeNode* root, const Segment2d& s2d) {
    if(root == nullptr) { // 空节点
        return;
    }
    dfs_cnt += 1;
    if(root -> s2d != nullptr) { // 叶子节点
        getIntersectForS2d(ans, *(root -> s2d), s2d); // 两个线段求交点的情况
        return;
    }
    if(root -> aabb.unlap(s2d.getAABB())) { // 处理没有重叠的情况
        return;
    }
    for(int i = 0; i <= 1; i += 1) {
        assert(root -> ch[i] != nullptr); // 由于前面已经判断了叶子节点的情况，所以这里一定是非叶子节点
        getAllIntersectIn(ans, root -> ch[i], s2d);
    }
    return;
}

long long SegmentKdTree::getDfsCnt() const {
    return dfs_cnt;
}