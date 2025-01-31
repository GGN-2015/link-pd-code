#include "NearestPoint.h"

#include <cstdio>

#ifdef TEST_NEAREST_POINT

int main() {
    int n; scanf("%d", &n);
    Point2dList p2dl;
    for(int i = 1; i <= n; i ++) {           // 输入所有点的坐标 
        int x, y; scanf("%d%d", &x, &y);
        p2dl.push_back((Point2d){(double)x, (double)y});
    }
    long long ans = NearestPoint(p2dl).getMinDis();
    printf("%lld\n", ans);                   // 输出最近点对距离 
    return 0;
}

#endif