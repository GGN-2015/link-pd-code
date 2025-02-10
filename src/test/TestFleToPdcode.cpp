#include <iostream>

#include <test/TestUtils.h>
#include <FileToPdCode.h>

#include <cassert>
using namespace std;

void testFileToPdCode() {
    for(const auto& file_path: TEST_FILE_LIST) {
        cout << INFO_FLAG << file_path<< endl;
        auto seed = 42;
        auto app  = FileToPdCode(fopen(file_path.c_str(), "r"), seed);
        auto pd_code = app.getPdCode();
        cout << INFO_FLAG << Serialize(pd_code) << endl;
        cout << INFO_FLAG << app.getDfsCnt() << endl;
    }
    assert(false);
}