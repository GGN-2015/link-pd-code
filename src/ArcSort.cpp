#include <algorithm>
#include <ArcSort.h>
#include <cassert>
#include <DataType.h>
using namespace std;

ArcSort::ArcSort(std::string name, std::vector<SegmentIdRatePair> sidrp) {
    assert(sidrp.size() >= 1);

    component_name = name;
    id_rate_pair_list = sidrp;
    sort(id_rate_pair_list.begin(), id_rate_pair_list.end()); // 从小到大排序
}

std::string ArcSort::getBeforeName(SegmentIdRatePair pr) const {
    int pos = lower_bound(id_rate_pair_list.begin(), id_rate_pair_list.end(), pr) - id_rate_pair_list.begin();
    assert(pr == id_rate_pair_list[pos]);
    char str[20];
    sprintf(str, "s_%06d", pos);
    return std::string("c_") + component_name + "#" + str;
}

std::string ArcSort::getAfterName(SegmentIdRatePair pr) const {
    int pos = lower_bound(id_rate_pair_list.begin(), id_rate_pair_list.end(), pr) - id_rate_pair_list.begin();
    assert(pr == id_rate_pair_list[pos]);
    if(pos == (int)id_rate_pair_list.size() - 1) { // 特殊处理最后一段即可
        pos = 0;
    }else {
        pos += 1;
    }
    char str[20];
    sprintf(str, "s_%06d", pos);
    return std::string("c_") + component_name + "#" + str;
}

std::string ArcSort::serialize() const {
    return "(" + component_name + "," + Serialize(id_rate_pair_list) + ")";
}