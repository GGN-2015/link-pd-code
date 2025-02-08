#pragma once

// 用于从某个文件指针输入一个 Link 信息

#include <cstdio>
#include <DataType.h>
#include <ProjectCoord.h>

class LinkInput {
public:
    LinkInput(std::mt19937& gen);
    ~LinkInput();
    void input(FILE* fpin);

    int getComponetCnt() const;
    int getComponentLength(int component_id) const;
    Segment3d getSegment(int component_id, int segment_id) const;

    bool checkRandomProject() const;      // 检查是否可以进行随机投影
    void getRandomProject(LinkInput* li); // 获取随机投影，存入一个指定 LinkInput

    std::string serialize() const;

private:
    Point3dList getPoint3dList() const; // 获得所有点构成的 List 用于随机投影

    int component_cnt; // 连通分支数量
    std::vector<Point3dList> components; // 记录每个连通分支的信息
    Point3dList all_point3d;

    ProjectCoord* pc;
    std::mt19937& gen;
};