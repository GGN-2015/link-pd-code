// 给定所有交点，不进行弧线编号替换，计算得到一个 PD_CODE
#pragma once

#include <ArcSort.h>
#include <map>
#include <DataType.h>
#include <EncodeCrossing.h>
#include <LinkInput.h>
#include <tuple>

class FirstParse {
public:
    FirstParse(LinkInput& link_input);
    std::vector<CrossingCode> getFirstParseCode();
    std::vector<CrossingCode> getSecondParseCode();
    int getDfsCnt() const;

private:
    int component_cnt;
    int no_crossing_component_cnt;
    LinkInput& link_input;

    std::vector<IntersectionRecord> ir_vec;
    std::vector<int> pair_vec;

    std::map<int, std::vector<std::tuple<int, double> > > bucket; // 把所有节点装到桶里
    std::map<int, ArcSort> arc_sort_bucket;

    int dfs_cnt;
};