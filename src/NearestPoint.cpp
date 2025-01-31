// 修改自我自己 2023-03-23 写的平面最近点对
// 提交记录：https://www.luogu.com.cn/record/200874900

#include <cassert>
#include <cmath>
#include <cstdio>

#include "NearestPoint.h"
using namespace std;

double NearestPoint::getMinDis() const {
    return m_minDis;
}

void NearestPoint::merge(int L, int mid, int R) {          // 按照 y 坐标进行归并排序的合并操作 
    lcnt = 0;                                // 借用 Ltmp 临时数组进行归并排序 
    int i = L, j = mid + 1;                  // i, j 分别为左侧数组和右侧数组的 "当前元素" 
    while(i <= mid && j <= R) {
        if(ps[i].y != ps[j].y ? ps[i].y < ps[j].y : ps[i].x < ps[j].x) {
                                             // 按照 y 坐标从小到大排序 
            Ltmp[++ lcnt] = ps[i];
            i ++;
        }else {
            Ltmp[++ lcnt] = ps[j];
            j ++;
        }
    }
    while(i <= mid) {                        // 左侧数组中仍有剩余元素 
        Ltmp[++ lcnt] = ps[i];
        i ++;
    }
    while(j <= R) {                          // 右侧数组中仍有剩余元素 
        Ltmp[++ lcnt] = ps[j];
        j ++;
    }
    for(int i = 1; i <= lcnt; i ++) {        // 将临时数组中的数据拷贝回 ps 数组 
        ps[L + i - 1] = Ltmp[i];
    }
}

double NearestPoint::solve(int L, int R) {              // 递归计算区间 [L, R] 的最小距离，并将点按照 y 坐标排序 
    const auto inf = std::numeric_limits<double>::infinity();
    if(L >= R) return inf;                   // 空区间 / 只有一个节点的区间不需要计算
    int mid  = (L + R) >> 1;
    int midx = ps[mid].x;
    double lans = solve(L,   mid);        // 递归计算左半区间和右半区间 
    double rans = solve(mid+1, R);
    double D = min(lans, rans);
    double mindis = inf;
    lcnt = 0;
    for(int i = L; i <= mid; i ++) {         // 载入左半区间距中轴线距离 <= sqrt(mindis) 的点 
        if(sqr(midx - ps[i].x) <= D) {
            Ltmp[++ lcnt] = ps[i];
        }
    }
    rcnt = 0;
    for(int i = mid+1; i <= R; i ++) {       // 载入右半区间距中轴线距离 <= sqrt(mindis) 的点 
        if(sqr(ps[i].x - midx) <= D) {
            Rtmp[++ rcnt] = ps[i];
        }
    }
                                             // 注：Ltmp 和 Rtmp 中的数据是按照 Y 坐标有序的 
    int lpos = 1, rpos = 0;
    for(int i = 1; i <= lcnt; i ++) {        // 枚举 Ltmp 中的点的点 
        while(rpos < rcnt && 
            (Rtmp[rpos + 1].y < Ltmp[i].y || sqr(Rtmp[rpos + 1].y - Ltmp[i].y) <= D)) {
            rpos ++;
        }
        while(lpos < rcnt && Ltmp[i].y > Rtmp[lpos].y && sqr(Ltmp[i].y - Rtmp[lpos].y) > D) {
            lpos ++;
        }
        for(int j = lpos; j <= rpos; j ++) { // Rtmp[lpos .. rpos] 是 日字形中的点 
            mindis = min(mindis, dis(Ltmp[i], Rtmp[j]));
        }
    }
    merge(L, mid, R);                        // 归并排序的合并操作 
    return min(D, mindis);
}

NearestPoint::NearestPoint(const Point2dList& point2dList): 
    Ltmp(point2dList.size() + 1), 
    Rtmp(point2dList.size() + 1),
    lcnt(0),
    rcnt(0)
{
    ps = point2dList;       // 拷贝构造
    assert(ps.size() >= 2); // 至少要有两个元素

    sort(ps.begin(), ps.end(), cmpx);
    m_minDis = solve(0, ps.size() - 1);
}