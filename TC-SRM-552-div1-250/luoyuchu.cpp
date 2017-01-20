#include <bits/stdc++.h>

using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)
template <class TAT>
inline void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>
inline void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}
typedef long long LL;

class FoxPaintingBalls {
    public:
    long long theMax(long long R, long long G, long long B, int N) {
        long long Z[2] = {0};//一个三角形需要的球的数量， Z[0]表示多的那种球，Z[1]表示少的那种
        long long g[3] = {0};//三种颜色的球的数量
        Z[0] = Z[1] = (LL)(N / 3) * (N / 3 - 1) / 2 * 3 + (N / 3) * 2;
        if (N % 3 == 1) Z[0] += (N / 3) + 1, Z[1] += (N / 3);
        if (N % 3 == 2) Z[0] += (N / 3) * 2 + 1, Z[1] += (N / 3) * 2 + 1;//计算需要的球数
        g[0] = R, g[1] = B, g[2] = G;
        sort(g, g + 3);
        if (Z[1] == 0) return (g[0] + g[1] + g[2]) / Z[0];//如果N =1，那么答案是球的个数之和
        else if (Z[0] == Z[1]) {
            return g[0] / Z[0];//如果一个三角形需要的不同颜色的球的数量相同，则答案是最小的颜色的球数除以需求
        }
        else {
            long long Ans = g[1] + g[2] - g[0] * 2;
            if (Ans >= g[0] / Z[1]) return g[0] / Z[1];//先用多的两种球组成需要多的颜色
            else {//之后再轮流组成多的颜色
                g[0] -= Z[1] * Ans;
                Ans += g[0] / (Z[0] + Z[1] + Z[1]) * 3;
                g[0] %= (Z[0] + Z[1] + Z[1]);
                if (g[0] >= Z[0] + Z[1]) Ans += 2;
                else if (g[0] >= Z[0]) Ans += 1;
                return Ans;
            }
        }
    }
};
