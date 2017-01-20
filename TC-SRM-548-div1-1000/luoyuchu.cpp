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

const int maxn = 53;
const int mod = 1e9+7;

int n, m, K;
int ye[maxn];//ye[i]->i个点的图的最大边数
int f[maxn][maxn];//Dp数组，f[i][j]->有编号的i个点j条边所组成连通图的方案数
int g[maxn][maxn];//Dp数组，g[i][j]->被限制点0所连接起来的两个联通块的大的具有i个点j条边的图的方案数
int C[maxn * maxn][maxn];//预处理的组合数

void Get_Comb()//计算组合数
{
    for (int i = 0; i <= 2500; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= min(i, 50); ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
}

void Calc_edge()//计算个点的图的最大边数
{
    for (int i = 0; i <= 50; ++i) {
        ye[i] = (i - 1) * i / 2;
    }
}

void Dp()//动态规划得出有编号的i个点j条边所组成连通图的个数
{
    f[0][0] = 1;
    f[1][0] = 1;
    for (int i = 2; i <= 50; ++i) {
        for (int j = 0; j <= 50; ++j) {
            int S = 0;
            for (int k = 1; k < i; ++k) {
                for (int p = 0; p <= j; ++p) {
                    S = (S + (LL)C[i - 1][k - 1] * f[k][p] % mod * C[ye[i - k]][j - p] % mod) % mod;
                }
            }
            f[i][j] = (C[ye[i]][j] - S + mod) % mod;
        }
    }
}

void Prepare()//预处理工作
{
    Get_Comb();
    Calc_edge();
    Dp();
}

int Onepoint(int _n, int _K)//针对m为1的情况的对策
{
    int Ans = 0;
    int S = 0;
    for (int i = 0; i <= _n - 3; ++i) {//当分为两个联通块时，枚举两边分别的大小
        for (int j = 0; j <= _K - 2; ++j)  {
            S = (S + (LL)f[1 + i][j] * f[_n - i - 2][_K - 2 - j] % mod * C[_n - 3][i] % mod) % mod;
        }
    }
    S = (LL)S * C[_n - 1][2] % mod;//枚举限制点连的两个点
    Ans = (Ans + S) % mod;
    Ans = (Ans + (LL)f[_n - 1][_K - 2] * C[_n - 1][2] % mod) % mod;//加上只有一个联通块的方案数
    return Ans;
}

int Onepoint_2part(int _n, int _K)//用于处理m为1且分为2个联通块的情况
{
    int S = 0;
    for (int i = 0; i <= _n - 3; ++i) {//当分为两个联通块时，枚举两边分别的大小
        for (int j = 0; j <= _K - 2; ++j)  {
            S = (S + (LL)f[1 + i][j] * f[_n - i - 2][_K - 2 - j] % mod * C[_n - 3][i] % mod) % mod;
        }
    }
    S = (LL)S * C[_n - 1][2] % mod;//枚举限制点连的两个点
    return S;
}

int Twopoint()//针对m为2的情况的对策
{
    int S, Sc;
    int Ans = 0;
    if (K < 3) return 0;
    //一个联通块
    Ans = (Ans + (LL)f[n - 2][K - 3] * (n - 2) % mod * (n - 2) % mod) % mod;//计算两个限制点共一条边，且剩余部分为1个联通块的方案数
    if (K >= 4) Ans = (Ans + (LL)f[n - 2][K - 4] * C[n - 2][2] % mod * C[n - 2][2] % mod) % mod;//计算两个限制点不共边，且剩余部分为1个联通块的方案数
    //两个联通块
    //总的思路是先枚举与限制点直接相连的是那两个点，再将剩下的点划分到限制点两边，再用事先处理的图的方案数计算
    S = 0;
    for (int i = 1; i <= n - 4; ++i) {
        for (int j = 0; j <= K - 4; ++j) {
            S = (S + (LL)f[1 + i][j] * f[n - 3 - i][K - 4 - j] % mod * C[i + 1][2] % mod * C[n - 4][i] % mod) % mod;
        }
    }
    S = (LL)S * (n - 2) % mod * (n - 3) % mod;
    S = S * 2 % mod;
    Ans = (Ans + S) % mod;//其中有一个限制点连在一个联通块上，另一个将两个联通块链接
    S = 0;
    for (int i = 0; i <= n - 4; ++i) {
        for (int j = 0; j <= K - 3; ++j) {
            S = (S + (LL)f[i + 1][j] * f[n - 3 - i][K - 3 - j] % mod * C[n - 4][i] % mod) % mod;
        }
    }
    S = (LL)S * (n - 2) % mod * (n - 3) % mod;
    Ans = (Ans + S) % mod;//两个限制点共一条边，且将两个联通块相连
    S = 0;
    for (int i = 0; i <= n - 4; ++i) {
        Sc = 0;
        for (int j = 0; j <= K - 4; ++j) {
            Sc = (Sc + (LL)f[i + 1][j] * f[n - 3 - i][K - 4 - j] % mod * C[n - 4][i] % mod) % mod;
        }
        S = (S + (LL)Sc * (i + 1) % mod * (n - 3 - i) % mod) % mod;
    }
    S = (LL)S * C[n - 2][2] % mod;
    Ans = (Ans + S) % mod;//两个限制点一起连接两个联通块
    //三个联通块
    //先按照两个联通块的思路处理，预处理出所有的两个联通块构成的块，再加上剩下一个联通块
    for (int i = 3; i <= n; ++i) {
        for (int j = 2; j <= K; ++j) {
            g[i][j] = Onepoint_2part(i, j);//预处理其中一个限制点所拼接的两个联通块的情况
        }
    }
    S = 0;
    for (int i = 2; i <= n - 3; ++i) {
        for (int j = 2; j <= K - 2; ++j) {
            S = (S + (LL)g[i + 1][j] * f[n - 2 - i][K - 2 - j] % mod * C[n - 4][i - 1] % mod) % mod;//将两个联通块与剩下一个合并
        }
    }
    Ans = (Ans + (LL)S * (n - 2) % mod * (n - 3) % mod) % mod;
    return Ans;
}

int Solve()
{
    if (m == 0) {//m=0
        return f[n][K];
    }
    else if (m == 1) {//m=1
        return Onepoint(n, K);
    }
    else {//m=2
        return Twopoint();
    }
}

class KingdomAndCities {
    public:
    int howMany(int _N, int _M, int _K) {
        n = _N;
        m = _M;
        K = _K;
        Prepare();
        return Solve();
    }
};
