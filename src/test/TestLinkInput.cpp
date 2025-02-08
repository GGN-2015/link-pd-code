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
        cout << OK_FLAG << li.serialize() << endl;
        assert(li.serialize() == "[[(0.000000,0.000000,0.000000),(0.000000,1.000000,0.000000),(1.000000,0.000000,0.000000)],[(0.400000,0.400000,0.000000),(0.400000,1.000000,-1.000000),(1.000000,0.400000,1.000000)]]");
        cout << OK_FLAG << li.serialize() << endl;
        
        LinkInput nli(gen);
        assert(li.checkRandomProject());
        li.getRandomProject(&nli);
        cout << OK_FLAG << nli.serialize() << endl;
        assert(nli.serialize() == "[[(0.000000,0.000000,0.000000),(0.162386,0.710695,0.684503),(0.705141,0.401673,-0.584325)],[(0.347011,0.444947,0.040071),(-0.245780,1.448921,0.014859),(1.460318,0.108394,0.125390)]]");
        cout << OK_FLAG << nli.serialize() << endl;

        auto [vir, pir] = li.getAllIntersect();
        assert(Serialize(pir) == "[2,3,0,1]");
        assert(Serialize(vir) == "[(0,1,0.400000),(0,1,0.600000),(1,0,0.333333),(1,2,0.666667)]");
        cout << OK_FLAG << Serialize(vir) << endl;
    }
}
