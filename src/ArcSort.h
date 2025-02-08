// 用于给同一个联通分支上的所有交叉点排序
#pragma once

#include <string>
#include <tuple>
#include <vector>

typedef std::tuple<int, double> SegmentIdRatePair;

class ArcSort {
public:
    ArcSort(std::string name, std::vector<SegmentIdRatePair> sidrp);

    std::string getBeforeName(SegmentIdRatePair pr) const; // 进入交叉点前的弧线名称
    std::string getAfterName(SegmentIdRatePair pr) const; // 进入交叉点后的弧线名称

    std::string serialize() const;

private:
    std::string component_name; // 记录当前 component 的名字
    std::vector<SegmentIdRatePair> id_rate_pair_list; // 记录所有线段编号和 rate 构成的二元组
};