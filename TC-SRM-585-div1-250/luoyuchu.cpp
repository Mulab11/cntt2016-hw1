#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

template <class TAT>
void Ckmax(TAT &a, const TAT &b)
{
    if (a < b) a = b;
}
template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
    if (a > b) a = b;
}

typedef long long LL;

const int mod = 1e9+7;

class TrafficCongestion {
    public:
    int theMinCars(int treeHeight) {
        int now = 1;
        //我们发现，对于所有深度为奇数的树，最有解一定可以构造为根节点只有单独的一个车不动
        //对于偶数的最优解根节点一定不为任何一辆车的起点或终点
        for (int i = 1; i <= treeHeight; ++i) {
            if (i & 1) {
                now = (now * 2 % mod - 1 + mod) % mod;
            }
            else {
                now = (now * 2 + 1) % mod;
            }
        }
        return now;
    }
};
