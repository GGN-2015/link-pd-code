// 用于编码一个交叉点
// arc_a_in 和 arc_a_out 用于描述线段 a 上的入弧线和出弧线的编码
// arc_b_in 和 arc_b_out 用于描述线段 b 上的入弧线和出弧线的编码

#include <algorithm>
#include <string>
#include <DataType.h>
#include <tuple>

// 编码规则是：
// 从下方进入的弧线开始，顺时针旋转，考虑所有弧线

class EncodeCrossing {
public:
    EncodeCrossing(const Segment3d& s3d_a, const Segment3d& s3d_b, std::string arc_a_in, std::string arc_a_out, std::string arc_b_in, std::string arc_b_out);
    CrossingCode getCode() const;

private:
    CrossingCode code;
};