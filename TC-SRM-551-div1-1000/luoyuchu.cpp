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

const int maxn = 45;
const int maxm = 184799;
const int mod = 1e9+7;

int n;
int broken, Maxval;
int item[maxn];
int mat[maxn][maxn];
int Less[maxn], Exact[maxn];
int C[maxn][maxn];

int Part[2][21][maxm];
int partcnt[2][21];

void Get_comb()//预处理组合数
{
    for (int i = 0; i < maxn; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
}

int Gauss()//高斯消元，求基尔霍夫矩阵的行列式
{
    int B, Sw = 0, Ans = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            while (mat[j][i] != 0) {
                for (int k = i; k < n; ++k) swap(mat[j][k], mat[i][k]);//消元
                B = mat[j][i] / mat[i][i];
                for (int k = i; k < n; ++k) mat[j][k] = (mat[j][k] - (LL)B * mat[i][k] % mod + mod) % mod;
                ++Sw;
            }
        }
        if (mat[i][i] == 0) return 0;
    }
    for (int i = 1; i < n; ++i) {
        Ans = (LL)Ans * mat[i][i] % mod;
    }
    if (Sw & 1) Ans = mod - Ans;//行列式交换两行的次数为奇数次值要取反
    return Ans;
}

void Prepare()//预处理有x个真正甜的水果的方案数
{
    static int du[maxn];
    for (int i = 0; i <= n - broken; ++i) {
        memset(du, 0, sizeof(du));
        memset(mat, 0, sizeof(mat));
        //真正甜的水果
        for (int j = 1; j <= i; ++j) {
            for (int k = 1; k <= i; ++k) {
                mat[j][k] = mod - 1;
            }
            for (int k = n - broken + 1; k <= n; ++k) {
                mat[j][k] = mod - 1;
            }
            mat[j][j] = i + broken - 1;
        }
        //不是真正甜的甜水果
        for (int j = i + 1; j <= n - broken; ++j) {
            for (int k = n - broken + 1; k <= n; ++k) {
                mat[j][k] = mod - 1;
            }
            mat[j][j] = broken;
        }
        //苦的水果
        for (int j = n - broken + 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                mat[j][k] = mod - 1;
            }
            mat[j][j] = n - 1;
        }
        Less[i] = Gauss();
    }
    //容斥原理算方案数
    for (int i = 0; i <= n - broken; ++i) {
        Exact[i] = Less[i];
        for (int j = 0; j < i; ++j) {
            Exact[i] = (Exact[i] - (LL)Exact[j] * C[i][j] % mod + mod) % mod;
        }
    }
    /*
    for (int i = 0; i < n - broken; ++i) {
        dig("%d : %d  %d\n", i, Less[i], Exact[i]);
    }
    dig("\n");
    */
}

void Enumeration()//预处理meet in the middle两边的方案数
{
    int total, N, half[2];
    int sum, cnt, tmp, *A;
    memset(partcnt, 0, sizeof(partcnt));
    sort(item + 1, item + 1 + n);
    reverse(item + 1, item + 1 + n);
    total = n - broken;
    half[0] = total / 2;//第一部分的大小
    half[1] = total - half[0];//第二部分的大小
    for (int T = 0; T < 2; ++T) {
        N = (1 << half[T]);
        if (T == 0) A = item;
        else A = item + half[0];
        for (int i = 0; i < N; ++i) {//枚举这一部分那些是真正甜的
            cnt = 0;
            sum = 0;
            tmp = i;
            for (int j = 1; j <= half[T]; ++j) {
                if (tmp & 1) {
                    ++cnt;
                    sum += A[j];
                }
                tmp >>= 1;
            }
            Part[T][cnt][++partcnt[T][cnt]] = sum;
        }
        for (int i = 0; i < half[T]; ++i) sort(Part[T][i] + 1, Part[T][i] + 1 + partcnt[T][i]);//排序
    }
}

int Solve()//meet in the middle搜索
{
    int p;
    int Ans = 0;
    int half[2];
    half[0] = (n - broken) / 2;
    half[1] = n - broken - half[0];
    for (int T = 0; T <= n - broken; ++T) {
        if (Exact[T] == 0) continue;
        for (int i = 0; i <= T; ++i) {
            if (i > half[0] || T - i > half[1]) continue;
            p = partcnt[1][T - i];
            for (int j = 1; j <= partcnt[0][i]; ++j) {
                while (p > 0 && Part[0][i][j] + Part[1][T - i][p] > Maxval) --p;//两部分具有单调性，一边增加，另一边一定减少
                if (p == 0) break;
                Ans = (Ans + (LL)p * Exact[T]) % mod;
            }
        }
    }
    return Ans;
}

class SweetFruits {
    public:
    int countTrees(vector<int> sweetness, int maxSweetness) {
        n = sweetness.size();
        Maxval = maxSweetness;
        sort(sweetness.begin(), sweetness.end());
        for (int i = 0; i < n; ++i) item[i + 1] = sweetness[i];
        broken = 0;
        while (broken < n && sweetness[broken] == -1) ++broken;//统计有多少个苦的水果
        Get_comb();//预处理组合数
        Prepare();//预处理有x个真正甜的水果的方案数
        Enumeration();//预处理meet in the middle两边的方案数
        return Solve();//meet in the middle搜索
    }
};
