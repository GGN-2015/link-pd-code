#include <cassert>
#include <SegmentKdTree.h>

SegmentKdTree::SegmentKdTree(const Segment2dList& s2dl) {
    assert(s2dl.size() >= 1);
    root = build(s2dl);
}

KdTreeNode* SegmentKdTree::build(const Segment2dList& s2dl) {
    assert(s2dl.size() >= 1);
    KdTreeNode* newNode = new KdTreeNode;
    if(s2dl.size() == 1) { // 叶子节点
        newNode -> ch[0] = newNode -> ch[1] = nullptr;
        newNode -> aabb  = s2dl[0].getAABB();
    }else {

    }
    return newNode;
}