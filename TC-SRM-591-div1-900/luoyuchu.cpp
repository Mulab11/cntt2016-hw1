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

const int maxn = 9;
const int maxs = 8e4+115;
const int mod = 1e9+9;

class StringPath {
    public:
    int countBoards(int n, int m, string A, string B) {
        static int f[2][maxs];
        int N = (1 << (m << 1));
        int nt = 0, s, rs;
        int Ans = 0;
        memset(f, 0, sizeof(f));//dp套dp，对于内层的两个Dp，两个状态都为状态为g[i][j]=0/1表示走到(i,j)这条路径是否满足
        //所以对于外层Dp：f[i][j][S]表示到了(i,j)，以这个点为折点的轮廓线上的每一个g的状态为S的方案数
        f[nt][3] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                memset(f[nt ^ 1], 0, sizeof(f[nt ^ 1]));
                for (int k = 1; k < N; ++k) {
                    if (f[nt][k] == 0) continue;
                    if (j != 0) {
                        s = ((k >> (j * 2 - 2)) & 3) | ((k >> (j * 2)) & 3);
                    }
                    else {
                        s = ((k >> (j << 1)) & 3);
                    }
                    rs = k ^ (((k >> (j << 1)) & 3) << (j << 1));
                    if (A[i + j] == B[i + j]) {//转移时直接枚举下一个格子是什么字母，然后按照g[i][j]的转移方式转移即可
                        (f[nt ^ 1][rs ^ ((s & 3) << (j << 1))] += f[nt][k]) %= mod;
                        (f[nt ^ 1][rs ^ ((s & 0) << (j << 1))] += 25LL * f[nt][k] % mod) %= mod;
                    }
                    else {
                        (f[nt ^ 1][rs ^ ((s & 1) << (j << 1))] += f[nt][k]) %= mod;
                        (f[nt ^ 1][rs ^ ((s & 2) << (j << 1))] += f[nt][k]) %= mod;
                        (f[nt ^ 1][rs ^ ((s & 0) << (j << 1))] += 24LL * f[nt][k] % mod) %= mod;
                    }
                }
                nt ^= 1;
            }
        }
        for (int k = 0; k < N; ++k) {
            if (((k >> (m * 2 - 2)) & 3) == 3) {//将满足要求的状态计入答案
                (Ans += f[nt][k]) %= mod;
            }
        }
        return Ans;
    }
};
