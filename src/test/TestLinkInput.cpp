#include <iostream>

#include <test/TestUtils.h>
#include <LinkInput.h>
#include <DataType.h>

#include <cassert>
using namespace std;

void testLinkInput() {
    {
        const unsigned int seed = 42; // 定义一个固定的随机种子
        std::mt19937 gen(seed);       // 使用固定种子初始化 std::mt19937 随机数生成器
        auto li = LinkInput(gen);
        FILE* fpin = fopen("./src/test/data/TestLinkInput.txt", "r");
        li.input(fpin);
        fclose(fpin);
        assert(li.serialize() == "[[(0.000000,0.000000,0.000000),(0.000000,1.000000,0.000000),(1.000000,0.000000,0.000000)],[(0.500000,0.500000,0.000000),(0.500000,1.000000,-1.000000),(1.000000,0.500000,1.000000)]]");
        cout << OK_FLAG << li.serialize() << endl;
        
        LinkInput nli(gen);
        assert(li.checkRandomProject());
        li.getRandomProject(&nli);
        assert(nli.serialize() == "[[(0.000000,0.000000,0.000000),(0.162386,0.710695,0.684503),(0.705141,0.401673,-0.584325)],[(0.433763,0.556184,0.050089),(-0.175266,1.489088,-0.043573),(1.476556,0.179463,0.193841)]]");
        cout << OK_FLAG << nli.serialize() << endl;
    }
}
