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

LL T;

LL Get2(LL x)//求出x!中有多少个2的因子
{
    LL S = 0;
    while (x) {
        S += (x >>= 1);
    }
    return S;
}

char Check(LL x, LL y)//检查(x,y)位置对应的组合数是偶数还是奇数
{
    if (x < y || (x + y) / 2 >= T || (x + y) & 1) {//超出范围或不对应一个组合数
        return '.';
    }
    if (Get2((x + y) / 2) - Get2(y) - Get2((x + y) / 2 - y) == 0) {//因子2的个数是否大于0
        if ((x + y) % 4 == 0) return 'A';
        else return 'B';
    }
    else return '.';
}

class CheckerExpansion {
    public:
    vector<string> resultAfter(long long t, long long x0, long long y0, int w, int h) {
        vector<string> Ans;
        Ans.resize(h);
        T = t;
        for (int i = 0; i < h; ++i) {
            Ans[i].resize(w);
            for (int j = 0; j < w; ++j) {
                Ans[i][j] = Check(x0 + j, y0 + h - i - 1);//枚举每一个位置，检查他的字符
            }
        }
        return Ans;//返回答案
    }
};
