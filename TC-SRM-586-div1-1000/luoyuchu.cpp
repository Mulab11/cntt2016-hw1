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
const int maxm = 27;

int n;
int A[maxn];
int ps[maxn];

int Solve1()//对于有且只有1个大于等于26的情况
{
    int mid;
    int Ans = 0;
    for (int i = 1; i <= n; ++i) {//找出大于等于26的人
        if (A[i] >= 26) {
            mid = i;
            break;
        }
    }
    int lmax = 0, rmax = 0;//两边直接向这个元素选取前缀与后缀即可
    Ans += A[mid] - 26;
    for (int i = 1; i < mid; ++i) {
        if (A[i] > lmax) {
            for (int j = lmax + 1; j <= A[i]; ++j) {
                Ans += ps[mid - 1] - ps[i - 1];
            }
            lmax = A[i];
        }
    }
    for (int i = n; i > mid; --i) {
        if (A[i] > rmax) {
            for (int j = rmax + 1; j <= A[i]; ++j) {
                if (j <= 26 - 1 - lmax) {
                    Ans += ps[i] - ps[mid];
                }
                else {
                    Ans += ps[i] - ps[mid] + A[mid] - 26;
                }
            }
            rmax = A[i];
        }
    }
    return Ans;
}

int Solve2()//对于多于1个的大于等于26的情况
{
    int mid1 = 2e9, mid2 = -2e9;
    int Ans = 0;
    for (int i = 1; i <= n; ++i) {//找出最左边的与最右边的>=26的
        if (A[i] >= 26) {
            Ckmin(mid1, i);
            Ckmax(mid2, i);
        }
    }
    Ans += 26 * (ps[mid2 - 1] - ps[mid1]);
    Ans -= 26;
    Ans += 25 * 26 + A[mid1] + A[mid2];
    int lmax = 0, rmax = 0;//两边还是像Solve1一样贪心，中间直接计算
    for (int i = 1; i < mid1; ++i) {
        if (A[i] > lmax) {
            for (int j = lmax + 1; j <= A[i]; ++j) {
                Ans += ps[mid1 - 1] - ps[i - 1] + A[mid1] - 26;
                if (j == 1) Ans -= A[mid1] - 26;
            }
            lmax = A[i];
        }
    }
    for (int i = n; i > mid2; --i) {
        if (A[i] > rmax) {
            for (int j = rmax + 1; j <= A[i]; ++j) {
                Ans += ps[i] - ps[mid2] + A[mid2] - 26;
                if (j == 1) Ans -= A[mid2] - 26;
            }
            rmax = A[i];
        }
    }
    return Ans;
}

int Solve0()//否则Dp
{
    static int f[2][maxm][maxm];//f[i][j][k]表示前i个元素，已经有k种字母不可能在之后出现了，有j种字母一定要在之后出现的最小代价
    static int nt = 0;
    int Ans = 2e9;
    nt = 0;
    memset(f, 0x3f, sizeof(f));
    f[nt][0][0] = 0;
    int b, c;
    for (int i = 1; i <= n; ++i) {
        memset(f[nt ^ 1], 0x3f, sizeof(f[nt ^ 1]));
        for (int j = 0; j <= 26; ++j) {
            for (int k = 0; k + j <= 26; ++k) {
                if (f[nt][j][k] < 1e9) {
                    for (int a = 0; a <= j && a <= A[i]; ++a) {
                        //枚举当前元素的组成方式：a种字母在以前出现过正好在这个元素最后一次出现，b种字母在这个元素第一次出现且以后一定会出现
                        //c种字母是以前出现过的而且以后一定会出现，d种字母在当前元素第一次出现且以后不会出现
                        //利用前缀和计算答案即可
                        c = min(A[i] - a, j - a);
                        for (int d = 0; d + j + k <= 26 && d + c + a <= A[i]; ++d) {
                            b = A[i] - c - d - a;
                            Ckmin(f[nt ^ 1][j - a + b][k + a + d], f[nt][j][k] + ps[i - 1] * a + a * (a + 1) / 2 - (ps[i] * b - b * (b - 1) / 2));
                        }
                    }
                }
            }
        }
        nt ^= 1;
    }
    for (int i = 0; i <= 26; ++i) {
        Ckmin(Ans, f[nt][0][i]);
    }
    return Ans;//返回答案
}

class StringWeight {
    public:
    int getMinimum(vector<int> L) {
        n = L.size();
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            A[i] = L[i - 1];
            ps[i] = ps[i - 1] + A[i];
            if (A[i] >= 26) ++cnt;
        }
        //对于某一种字母的贡献，可以看作相邻的同种字母两两求贡献
        //所以对于L数组中至少有1个大于等于26的情况，可以直接贪心选择，否则可以用Dp解决
        if (cnt == 1) return Solve1();//贪心
        else if (cnt >= 2) return Solve2();//贪心
        else return Solve0();//动态规划
    }
};
