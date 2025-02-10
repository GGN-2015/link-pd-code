#include <cassert>
#include <DataType.h>
#include <LinkInput.h>

using namespace std;

LinkInput::LinkInput(std::mt19937& n_gen): 
    component_cnt(0), components({}), all_point3d({}), gen(n_gen), dfs_cnt(0) {
    // 初始化时候什么都不做
    pc = nullptr;
}

LinkInput::~LinkInput() {
    if(pc != nullptr) {
        delete pc;
    }
}

int LinkInput::getDfsCnt() const {
    return dfs_cnt;
}

void LinkInput::input(FILE* fpin) {
    assert(fpin != nullptr); // 检查文件可以读写
    assert(pc == nullptr);    // 之前没有进行过 input 操作

    fscanf(fpin, "%d", &component_cnt);
    for(int i = 0; i < component_cnt; i += 1) { // 输入每一个连通分量
        int point_cnt;
        fscanf(fpin, "%d", &point_cnt); // 输入一个连通分量中的点数
        assert(point_cnt >= 3);         // 要求每个连通分支至少有三个点 

        Point3dList p3dl;
        for(int j = 0; j < point_cnt; j += 1) {
            Point3d p3d;
            p3d.input(fpin);
            p3dl.push_back(p3d);
            all_point3d.push_back(p3d); // 记录全部点集合
        }
        components.push_back(p3dl); // 记录每一个序列
    }
    pc = new ProjectCoord(gen, all_point3d); // 先随机生成一个投影方向
}

int LinkInput::getComponetCnt() const {
    return component_cnt;
}

int LinkInput::getComponentLength(int component_id) const {
    assert(0 <= component_id && component_id < getComponetCnt());
    return components[component_id].size();
}

Segment3d LinkInput::getSegment(int component_id, int segment_id) const {
    assert(0 <= component_id && component_id < getComponetCnt());
    assert(0 <= segment_id   && segment_id   < getComponentLength(component_id));

    if(segment_id == getComponentLength(component_id) - 1) { // 最后一个线段
        return Segment3d {
            components[component_id][segment_id],
            components[component_id][0],
            component_id,
            segment_id
        };
    }else {
        return Segment3d {
            components[component_id][segment_id],
            components[component_id][segment_id + 1],
            component_id,
            segment_id
        };
    }
}

Point3dList LinkInput::getPoint3dList() const { // 计算全部点集合
    return all_point3d;
}

bool LinkInput::checkRandomProject() const {
    assert(pc != nullptr);
    return pc -> test();
}

void LinkInput::getRandomProject(LinkInput* li) { // 获取一个随机投影方式
    assert(checkRandomProject());
    li -> component_cnt = component_cnt;
    li -> components    = components;
    li -> all_point3d   = all_point3d;
    li -> pc            = new ProjectCoord(gen, all_point3d); // 注意这里是新的 pc

    auto coord3d = pc ->getOneCoord3d(); // 注意这里用的是老的 pc
    for(auto& component: li -> components) {
        for(auto& p3d: component) {
            p3d = getNewCoordForPoint3d(p3d, coord3d);
        }
    }

    for(auto& p3d: li -> all_point3d) {
        p3d = getNewCoordForPoint3d(p3d, coord3d);
    }
}

std::string LinkInput::serialize() const {
    std::string ans = "[";
    bool first = true;
    for(const auto& component: components) {
        if(first) {
            first = false;
        }else {
            ans += ",";
        }
        ans += Serialize(component);
    }
    return ans + "]";
}

Segment3dList LinkInput::getAllSegments3d() const {
    Segment3dList ans {};
    for(int i = 0; i < component_cnt; i += 1) {
        for(int j = 0; j < getComponentLength(i); j += 1) {
            ans.push_back(getSegment(i, j));
        }
    }
    return ans;
}

Segment2dList LinkInput::getAllSegments2d() const {
    Segment2dList ans {};
    for(const auto& s3d: getAllSegments3d()) {
        ans.push_back(s3d.abandonZ());
    }
    return ans;
}

std::tuple<std::vector<IntersectionRecord>, std::vector<int>> LinkInput::getAllIntersect() {
    std::vector<IntersectionRecord> ans;
    auto s2dl = getAllSegments2d();
    auto skdt = SegmentKdTree(s2dl);
    for(const auto& s2d: s2dl) {
        auto vir = skdt.getAllIntersect(s2d);
        for(const auto& ir: vir) {
            ans.push_back(ir);
        }
    }
    dfs_cnt += skdt.getDfsCnt(); // 统计大概用了多少时间
    assert(ans.size() % 2 == 0); //  必须是偶数个交叉点才能配对
    sort(ans.begin(), ans.end(), IrCmp);
    
    std::vector<int> pair_vector(ans.size(), 0); // 构建配对情况
    std::vector<int> tool_vector;
    for(int i = 0; i < (int)ans.size(); i += 1) {
        tool_vector.push_back(i);
    }
    auto getCrossing = [&](int x) {
        auto cid_1 = ans[x].component_id;
        auto sid_1 = ans[x].segment_id;
        auto rat_1 = ans[x].rate;
        auto pt_1  = (this -> getSegment(cid_1, sid_1)).abandonZ().step(rat_1);
        return pt_1;
    };
    sort(tool_vector.begin(), tool_vector.end(), [&](int x, int y){
        return getCrossing(x) < getCrossing(y);
    });
    for(int i = 0; i < (int)tool_vector.size(); i += 1) {
        pair_vector[tool_vector[i]] = tool_vector[i^1];
    }
    for(int i = 0; i < (int)pair_vector.size(); i += 1) { // 检查配对是否合法
        if(i < pair_vector[i]) {
            auto j = pair_vector[i];
            auto pt_1  = getCrossing(i);
            auto pt_2  = getCrossing(j);
            assert(pt_1 == pt_2);
        }
    }
    return make_tuple(ans, pair_vector); // 返回所有出现的交点以及配对情况
}