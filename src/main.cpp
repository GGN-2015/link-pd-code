#include <cstdio>
#include "TestAll.h"
using namespace std;

int main() {

#ifdef TEST
    testAll();

#else
    printf("hello world!\n");

#endif

    return 0;
}
