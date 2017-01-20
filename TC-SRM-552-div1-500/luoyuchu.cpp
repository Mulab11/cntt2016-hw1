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

const int maxn = 31;
const int maxm = 31 * 31 * 2;
const int AD = 903;

int n, m, Maxval;
int Ans;
char mat[maxn][maxn];//矩阵
int sum[3][maxn][maxn];//二维前缀和
int part[maxn][maxm];
bool pe[maxn][maxm];
int me[maxm];
bool he[maxm];

int Getsum(int p, int u, int d, int l, int r)//求一个区域和和
{
    return sum[p][d][r] + sum[p][u - 1][l - 1] - sum[p][d][l - 1] - sum[p][u - 1][r];
}

void Solve()
{
    int L, R, t;
    memset(part, 0, sizeof(part));//part[i][j]表示在第i行及以下的所有子矩阵中，L的花比P的花多j朵的最大花数
    memset(pe, 0, sizeof(pe));//pe表示这个part是否存在
    for (int u = 1; u <= n; ++u) {//预处理每一个子矩阵的情况
        for (int d = u; d <= n; ++d) {
            for (int l = 1; l <= m; ++l) {
                for (int r = l; r <= m; ++r) {
                    Ckmax(part[u][t = (Getsum(0, u, d, l, r) - Getsum(1, u, d, l, r) + AD)], Getsum(2, u, d, l, r));
                    pe[u][t] = 1;
                }
            }
        }
    }
    for (int i = n - 1; i >= 1; --i) {//求前缀和，求出part
        for (int j = 0; j < maxm; ++j) {
            Ckmax(part[i][j], part[i + 1][j]);
            pe[i][j] |= pe[i + 1][j];
        }
    }
    for (int d = 1; d < n; ++d) {//枚举d行及以上的一个子矩阵
        memset(me, 0, sizeof(me));//me[i]表示d行及以上的所有子矩阵中，L的花比P的花多i朵的最大花数
        memset(he, 0, sizeof(he));//表示对应的me是否存在
        for (int u = 1; u <= d; ++u) {
            for (int l = 1; l <= m; ++l) {
                for (int r = l; r <= m; ++r) {
                    Ckmax(me[t = (Getsum(0, u, d, l, r) - Getsum(1, u, d, l, r) + AD)], Getsum(2, u, d, l, r));
                    he[t] = 1;
                }
            }
        }
        for (int i = 0; i < maxm; ++i) {//对于每一个me，枚举与之合法的part并更新答案
            if (!he[i]) continue;
            L = max(0, AD * 2 - Maxval - i);
            R = min(maxm * 2 - 1, AD * 2 + Maxval - i);
            for (int j = L; j <= R; ++j) {
                if (!pe[d + 1][j]) continue;
                Ckmax(Ans, me[i] + part[d + 1][j]);
            }
        }
    }
}

void Prepare()//求2维前缀和
{
    const char Cri[2] = {'L', 'P'};
    for (int T = 0; T < 2; ++T) {//1维前缀和
        for (int i = 1; i <= n; ++i) {
            sum[T][i][0] = 0;
            for (int j = 1; j <= m; ++j) {
                sum[T][i][j] = sum[T][i][j - 1] + (mat[i][j] == Cri[T]);
            }
            for (int j = 1; j <= m; ++j) {
                sum[T][i][j] += sum[T][i - 1][j];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {//2维前缀和
        for (int j = 1; j <= m; ++j) {
            sum[2][i][j] = sum[0][i][j] + sum[1][i][j];
        }
    }
}

void Trans()//将矩阵转置
{
    for (int i = 1; i <= max(n, m); ++i) {
        for (int j = 1; j <= i; ++j) {
            swap(mat[i][j], mat[j][i]);
        }
    }
    swap(n, m);
}

class FoxAndFlowerShopDivOne {
    public:
    int theMaxFlowers(vector<string> flowers, int maxDiff) {
        Ans = -1;
        Maxval = maxDiff;
        n = flowers.size();
        m = flowers[0].length();
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                mat[i][j] = flowers[i - 1][j - 1];
            }
        }
        Prepare();//求2维前缀和
        Solve();//meet in the middle 搜索
        Trans();//将矩阵转置
        Prepare();//求2维前缀和
        Solve();//meet in the middle 搜索
        return Ans;//返回答案
    }
};
