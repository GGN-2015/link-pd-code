// 给定一个 FILE* 文件
// 读入一个三维空间中的扭结并返回一个 PD_CODE
#pragma once

#include <cstdio>
#include <FirstParse.h>
#include <LinkInput.h>

class FileToPdCode {
public:
    FileToPdCode(FILE* file, const unsigned int seed);
    std::vector<CrossingCode> getPdCode() const;
    int getDfsCnt() const;

private:
    std::vector<CrossingCode> pd_code;
    int dfs_cnt;
};