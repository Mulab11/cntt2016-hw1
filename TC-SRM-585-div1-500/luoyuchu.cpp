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

const int maxn = 55;
const int maxm = 1355;
const int mod = 1e9+7;

int n, K;
int Card[maxn], pc[maxn];
int f[maxn][maxm];
int g[maxm][maxn];
int C[maxm][maxn];

void Prepare()//预处理组合数，以及本题需要用到的一种拆分数
{
    for (int i = 0; i < maxm; ++i) {
        C[i][0] = 1;
        for (int j = 1; j < maxn && j <= i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    g[0][0] = 1;//g[i][j]表示将j个无差别元素放入i个有差别的盒子的方案数
    for (int i = 1; i < maxm; ++i) {
        for (int j = 0; j < maxn; ++j) {
            for (int k = 0; k <= j; ++k) {
                (g[i][j] += g[i - 1][j - k]) %= mod;
            }
        }
    }
}

int Solve()
{
    const int N = 1296;
    memset(f, 0, sizeof(f));
    f[0][0] = 1;//f[i][j]表示使用前i种卡片拼成的序列的LISnum为j的方案数
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= N; ++j) {
            for (int k = 0; k <= Card[i] && k <= j; ++k) {//枚举新放入的卡片有几张是正好接在一个LIS序列末尾的，则LISnum会n增加Card[i]-k个
                (f[i][j + Card[i] - k] += (LL)f[i - 1][j] * C[j][k] % mod * g[pc[i - 1] + 1 - j + k][Card[i] - k] % mod) %= mod;
            }
        }
    }
    return f[n][K];
}

class LISNumber {
    public:
    int count(vector<int> cardsnum, int _K) {
        n = cardsnum.size();
        K = _K;
        memset(g, 0, sizeof(g));
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; ++i) {
            Card[i] = cardsnum[i - 1];
            pc[i] = pc[i - 1] + Card[i];//前缀和
        }
        Prepare();
        return Solve();
    }
};
