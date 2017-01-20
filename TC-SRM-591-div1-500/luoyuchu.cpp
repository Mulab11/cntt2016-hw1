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

int gcd(int a, int b)
{
    while (b) {
        b ^= a ^= b ^= a %= b;
    }
    return a;
}

class PyramidSequences {
    public:
    long long distinctPairs(int N, int M) {
        LL Ans = 0;//考虑数形结合，将两个序列看作x坐标与y坐标，则图形为一条遇到边界就反弹的折线，然后可以看出规律
        int g = gcd(N - 1, M - 1);
        Ans += (LL)(N - 1) / g * (M - 1) / g * (g - 1);//只被折线经过一次的点
        Ans += ((LL)((N - 1) / g + 1) * ((M - 1) / g + 1) + 1) / 2;//经过两次的点
        return Ans;
    }
};
