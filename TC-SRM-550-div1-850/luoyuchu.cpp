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

const int maxn = 87;
const int mod = 1e9+7;

int n, m;
LL Ec, Mc;
int Cnt[3];//需要步数的个数
int ys[maxn][maxn];//不同情况的标号

struct Matrix//矩阵
{
    int t[maxn][maxn];
    void reset()
    {
        memset(t, 0, sizeof(t));
    }
};

void Prepare()
{
    m = 0;
    for (int i = 0; i <= n; ++i) {//预处理标号
        for (int j = 0; i + j <= n; ++j) {
            ys[i][j] = m++;
        }
    }
    m++;
}

Matrix Mult(const Matrix &a, const Matrix &b)//矩阵乘法
{
    static Matrix s;
    s.reset();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                s.t[i][j] = (s.t[i][j] + (LL)a.t[i][k] * b.t[k][j]) % mod;
            }
        }
    }
    return s;
}

int Solve()
{
    Matrix Ans, S;
    int y;
    Ans.reset();
    S.reset();//转移矩阵
    for (int i = 0; i < m; ++i) Ans.t[i][i] = 1;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; i + j <= n; ++j) {
            if (i != 0) S.t[ys[i][j]][ys[i - 1][j]] += i;
            if (j != 0) S.t[ys[i][j]][ys[i + 1][j - 1]] += j;
            if (i + j != n) S.t[ys[i][j]][ys[i][j + 1]] += n - i - j;
        }
    }
    S.t[ys[0][0]][m - 1] = 1;
    S.t[m - 1][m - 1] = 1;//答案计数器
    y = Cnt[1] * 1 + Cnt[2] * 2 + Mc / Ec * 3;//可以走的步数
    while (y) {
        if (y & 1) Ans = Mult(Ans, S);
        S = Mult(S, S);
        y >>= 1;
    }
    return (Ans.t[ys[Cnt[1]][Cnt[2]]][m - 1] + Ans.t[ys[Cnt[1]][Cnt[2]]][ys[0][0]]) % mod;
}

class ConversionMachine {
    public:
    int countAll(string word1, string word2, vector<int> costs, int maxCost) {
        n = word1.length();
        memset(Cnt, 0, sizeof(Cnt));
        Ec = costs[0] + costs[1] + costs[2];//每一次回到原来的字符所需要的代价
        Mc = maxCost;//剩余可使用代价
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            LL sum = 0;
            while (word1[i] != word2[i]) {
                ++cnt;
                sum += costs[word1[i] - 'a'];
                word1[i] = ((word1[i] - 'a') + 1) % 3 + 'a';
            }
            Mc -= sum;//减去必须花去的代价
            if (Mc < 0) return 0;
            ++Cnt[cnt];
        }
        if (Mc < 0) return 0;
        Prepare();
        return Solve();//返回答案
    }
};
