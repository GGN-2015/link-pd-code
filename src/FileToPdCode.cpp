#include <FileToPdCode.h>

FileToPdCode::FileToPdCode(FILE* fpin, const unsigned int seed) {
    std::mt19937 gen(seed);       // 使用固定种子初始化 std::mt19937 随机数生成器
    auto li = LinkInput(gen);
    li.input(fpin);
    LinkInput nli(gen);
    li.getRandomProject(&nli); // 进行一次随机投影
    auto fp = FirstParse(nli);
    auto sp = fp.getSecondParseCode();
    pd_code = sp; // 生成一次 pd_code 以后可以考虑生成更多次 pd_code
}

std::vector<CrossingCode> FileToPdCode::getPdCode() const {
    return pd_code;
}