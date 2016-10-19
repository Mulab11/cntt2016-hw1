```c++
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

const int maxn = 23;
const int maxs = 151 * 9;

int n, m, S;
LL f[maxn][maxs][2];//Dp数组
int mat[maxn][maxn];//输入矩阵
bool hv[maxn];//每一行是否选
double Ans;//答案

void Dp()
{
    static int sum[maxn], cnt, fs;
    memset(sum, 0, sizeof(sum));
    cnt = 0;
    fs = 0;
    for (int i = 1; i <= n; ++i) {//如果这枚举的集合中包含这一行，则先要将在这一行个格子的和统计
        cnt += hv[i];
        if (hv[i]) {
            for (int j = 1; j <= m; ++j) {
                fs += mat[i][j];
            }
        }
    }
    for (int i = 1; i <= m; ++i) {//统计每一列除去枚举的行的格子的和
        for (int j = 1; j <= n; ++j) {
            if (!hv[j]) {
                sum[i] += mat[j][i];
            }
        }
    }
    memset(f, 0, sizeof(f));
    f[0][0][cnt & 1] = 1;
    for (int i = 0; i < m; ++i) {//Dp，枚举到了哪一列，现在的数字和是多少，集合大小为奇数还是偶数
        for (int j = 0; j < maxs; ++j) {
            for (int k = 0; k < 2; ++k) {
                f[i + 1][j][k] += f[i][j][k];
                if (j + sum[i + 1] < maxs) {
                    f[i + 1][j + sum[i + 1]][k ^ 1] += f[i][j][k];
                }
            }
        }
    }
    double tp;
    for (int i = 0; i < maxs; ++i) {//统计总的期望，根据容斥原理，奇减偶加
        if (f[m][i][1]) {
            tp = (S - i - fs) / (double)S;
            if (tp != 1) Ans += (1 + tp / (1 - tp)) * f[m][i][1];//特殊判断tp为1的情况
        }
        if (f[m][i][0]) {
            tp = (S - i - fs) / (double)S;
            if (tp != 1) Ans -= (1 + tp / (1 - tp)) * f[m][i][0];
        }
    }
}

void Solve()
{
    int N = (1 << n);
    int tmp;
    for (int i = 0; i < N; ++i) {//先枚举固定的行集合
        tmp = i;
        for (int j = 1; j <= n; ++j) {
            hv[j] = tmp & 1;
            tmp >>= 1;
        }
        Dp();
    }
}

class RandomPaintingOnABoard {
    public:
    double expectedSteps(vector<string> prob) {
        n = prob.size();
        m = prob[0].length();
        S = 0;
        Ans = 0;
        for (int i = 1; i <= n; ++i) {//输入
            for (int j = 1; j <= m; ++j) {
                mat[i][j] = prob[i - 1][j - 1] - '0';
                S += mat[i][j];//统计概率总和
            }
        }
        if (n > m) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= i; ++j) {
                    swap(mat[i][j], mat[j][i]);//总是将小的以为作为行，大的作为列
                }
            }
            swap(n, m);
        }
        Solve();
        return Ans;
    }
};

```