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
const int maxm = 1e6+115;

int n;
int f[2][maxm];

class MayTheBestPetWin {
    public:
    int calc(vector<int> A, vector<int> B) {
        int nt = 0;
        int Ans = 2e9;
        n = A.size();
        swap(A, B);
        memset(f, 0, sizeof(f));
        f[nt][0] = 1;
        //将A，B数组交换
        //考虑分为了两个集合s1,s2，我们要min(A(s1)-B(s2))，且A(s1)-B(s2)>A(s2)-B(s1)
        //这两个条件可以变为min(A(s1)+B(s1)-B(s1+s2))       A(s1)+B(s1)>A(s2)+B(s2)
        //直接求出有多少种可能的A(s1)+B(s1)即可
        for (int i = 0; i < n; ++i) {
            memset(f[nt ^ 1], 0, sizeof(f[nt ^ 1]));
            for (int j = 0; j < maxm; ++j) {
                if (f[nt][j]) {
                    f[nt ^ 1][j + A[i] + B[i]] = 1;
                    f[nt ^ 1][j] = 1;
                }
            }
            nt ^= 1;
        }
        int Sab = 0, Sb = 0;
        for (int i = 0; i < n; ++i) {
            Sab += A[i] + B[i];
            Sb += B[i];
        }
        for (int i = 0; i < maxm; ++i) {
            if (f[nt][i] && Sab - i <= i) {
                Ckmin(Ans, i - Sb);
            }
        }
        return Ans;
    }
};
