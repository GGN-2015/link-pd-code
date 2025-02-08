#include <cassert>
#include <iostream>

#include <FirstParse.h>
#include <test/TestUtils.h>
using namespace std;

void testFirstParse() {
    {
        const unsigned int seed = 42; // 定义一个固定的随机种子
        std::mt19937 gen(seed);       // 使用固定种子初始化 std::mt19937 随机数生成器
        auto li = LinkInput(gen);
        FILE* fpin = fopen("./src/test/data/TestLinkInput.txt", "r");
        li.input(fpin);
        fclose(fpin);
        assert(li.serialize() == "[[(0.000000,0.000000,0.000000),(0.000000,1.000000,0.000000),(1.000000,0.000000,0.000000)],[(0.400000,0.400000,0.000000),(0.400000,1.000000,-1.000000),(1.000000,0.400000,1.000000)]]");
        
        auto fp = FirstParse(li);
        assert(Serialize(fp.getFirstParseCode()) == "[(c_c_000000#s_000001,c_c_000001#s_000001,c_c_000000#s_000000,c_c_000001#s_000000),(c_c_000001#s_000000,c_c_000000#s_000000,c_c_000001#s_000001,c_c_000000#s_000001)]");
        cout << OK_FLAG << Serialize(fp.getFirstParseCode()) << endl;
    }
}