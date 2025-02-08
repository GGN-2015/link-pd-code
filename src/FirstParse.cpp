#include <FirstParse.h>
#include <iostream>
#include <set>
using namespace std;

FirstParse::FirstParse(LinkInput& link_input): link_input(link_input) {
    component_cnt = link_input.getComponetCnt();
    auto [ir_vec_tmp, pair_vec_tmp] = link_input.getAllIntersect(); // 求交点
    ir_vec   = ir_vec_tmp;
    pair_vec = pair_vec_tmp;

    for(const auto& ir: ir_vec) { // 把所有交叉点装进桶里
        bucket[ir.component_id].push_back(make_tuple(ir.segment_id, ir.rate));
    }

    for(const auto& item: bucket) { // 构建所有的排序桶
        const auto& [component_id, list] = item; // list 是当前连通分量对应的所有交叉点

        char c_name[20];
        sprintf(c_name, "c_%06d", component_id);
        arc_sort_bucket[component_id] = ArcSort(std::string(c_name), list);
    }

    no_crossing_component_cnt = 0; // 统计有多少个游离的连通分量
    for(int i = 0; i < component_cnt; i += 1) {
        if(bucket.count(i) == 0) no_crossing_component_cnt += 1;
    }
}

std::vector<CrossingCode> FirstParse::getFirstParseCode() { // 计算一个节点的编码
    auto ans = std::vector<CrossingCode> {};
    for(int i = 0; i < (int)pair_vec.size(); i += 1) {
        int j = pair_vec[i];
        if(i  < j) {
            auto s3d_a = link_input.getSegment(ir_vec[i].component_id, ir_vec[i].segment_id);
            auto s3d_b = link_input.getSegment(ir_vec[j].component_id, ir_vec[j].segment_id);
            auto a_in  = arc_sort_bucket[ir_vec[i].component_id].getBeforeName(make_pair(ir_vec[i].segment_id, ir_vec[i].rate));
            auto a_out = arc_sort_bucket[ir_vec[i].component_id].getAfterName (make_pair(ir_vec[i].segment_id, ir_vec[i].rate));
            auto b_in  = arc_sort_bucket[ir_vec[j].component_id].getBeforeName(make_pair(ir_vec[j].segment_id, ir_vec[j].rate));
            auto b_out = arc_sort_bucket[ir_vec[j].component_id].getAfterName (make_pair(ir_vec[j].segment_id, ir_vec[j].rate));
            auto ec = EncodeCrossing(s3d_a, s3d_b, a_in, a_out, b_in, b_out);
            if(ec.getErr() != "") {
                cout << ec.getErr() << ":" << ec.serialize() << endl;
            }
            assert(ec.getErr() == ""); // 不允许出错
            ans.push_back(ec.getCode());
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

std::vector<CrossingCode> FirstParse::getSecondParseCode() {
    auto first_parse_code = getFirstParseCode();
    auto ans = std::vector<CrossingCode> {};

    std::set<std::string> sort_set;
    for(const auto& corssing: first_parse_code) {
        for(const auto& arc: corssing.arc_name) {
            sort_set.insert(arc);
        }
    }
    std::map<std::string, int> sort_map;
    int val_cnt = 0; // 当前使用了多少个编号
    for(const auto& item: sort_set) { // 从 1 开始向上编号
        sort_map[item] = ++ val_cnt;
    }

    for(const auto& crossing: first_parse_code) {
        ans.push_back(CrossingCode{
            std::to_string(sort_map[crossing.arc_name[0]]),
            std::to_string(sort_map[crossing.arc_name[1]]),
            std::to_string(sort_map[crossing.arc_name[2]]),
            std::to_string(sort_map[crossing.arc_name[3]])
        });
    }

    for(int i = 0; i < no_crossing_component_cnt; i += 1) { // 为每个无交点的连通分量增加一个交点
        int vi = ++ val_cnt;
        int vj = ++ val_cnt;
        ans.push_back(CrossingCode{
            std::to_string(vi),
            std::to_string(vi),
            std::to_string(vj),
            std::to_string(vj)
        });
    }
    return ans;
}