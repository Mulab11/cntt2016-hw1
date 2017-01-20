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

int n, m;
LL A[maxn], aim;
bitset<maxn> mat[maxn];

LL Gauss()//高斯消元解方程组
{
    int p = 1;
    for (int i = 1; i <= n; ++i) {
        if (mat[p][i] != 1) {
            for (int j = p + 1; j <= m; ++j) {
                if (mat[j][i] == 1) {
                    swap(mat[p], mat[j]);
                    break;
                }
            }
        }
        if (mat[p][i] != 1) continue;
        for (int j = p + 1; j <= m; ++j) {
            if (mat[j][i]) {
                mat[j] = mat[j] ^ mat[p];
            }
        }
        ++p;
        if (p > m) break;
    }
    for (int i = m; i >= 1; --i) {
        if (mat[i][n + 1] == 1 && mat[i].count() == 1) return 0;//判断无解
        if ((int)mat[i].count() - (mat[i][n + 1] == 1) > 0) {
            return (1LL << (n - i));//2的自由元的个数的幂即为方程的解的个数
        }
    }
    return (1LL << n);
}

LL Calc(int l, int r, LL val)//计算二进制l~r位正好为val的方案数
{
    m = r - l + 1;
    for (int i = l; i <= r; ++i) {
        mat[i - l + 1].reset();
        mat[i - l + 1][n + 1] = ((val >> i) & 1);
        for (int j = 1; j <= n; ++j) {
            if ((A[j] >> i) & 1) {
                mat[i - l + 1][j] = 1;
            }
        }
    }
    return Gauss();
}

LL Solve()
{
    LL tmp = aim, S = 0;
    LL Ans = 0;//我们可以通过对每个二进制位列一个方程来求得xor等于一个数的解的个数
    for (int i = 50; i >= 0; --i) {//考虑将limit的每一个1变为0，则只要他之前的位置正好等于，之后的位置就可以随便取到全集，这样就转化为了求解xor等于一个数的方案数
        if ((tmp >> i) & 1) {
            Ans += Calc(i, 50, S);
            S += (1LL << i);
        }
    }
    Ans += Calc(0, 50, aim);//计算完全等于limit的方案数
    return Ans;
}

class XorCards {
    public:
    long long numberOfWays(vector<long long> number, long long limit) {
        n = number.size();
        aim = limit;
        for (int i = 1; i <= n; ++i) {
            A[i] = number[i - 1];
        }
        return Solve();//返回答案
    }
};
