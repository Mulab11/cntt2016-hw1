#include <vector>
using namespace std;
const int mod = 1e9 + 7;
const int MaxN = 60;
const int MaxM = 1250;
int comb[MaxM][MaxN];
int e[MaxN], f[MaxN][MaxN];
// f[i][j] : i 个点，j 条边的连通图

class KingdomAndCities
{
public:
    int howMany(int n, int N, int m)
    {
        if(m < n - 1) return 0;
        if(N == 1 && m < 2) return 0;
        if(N == 2 && m < 3) return 0;
        if(n == N)
        {
            if(n == 1) return m <= 0;
            if(n == 2) return m <= 1;
        }
        for(int i = 1; i <= n; ++i)
            e[i] = i * (i - 1) / 2;
        comb[0][0] = 1;
        for(int i = 1; i <= e[n] || i <= n; ++i)
        {
            comb[i][0] = comb[i][i] = 1;
            for(int j = 1; j <= i && (j <= n || j <= m); ++j)
                comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
        }
        f[1][0] = 1;
        for(int i = 2; i <= n; ++i)
            for(int j = i - 1; j <= e[i] && j <= m; ++j)
            {
                int tmp = comb[e[i]][j];
                for(int a = 1; a != i; ++a)
                {
                    int tmp1 = 0;
                    for(int b = a - 1; b <= e[a] && b <= j; ++b)
                        tmp1 = (tmp1 - (long long) f[a][b] * comb[e[i - a]][j - b]) % mod;
                    tmp = (tmp + (long long) tmp1 * comb[i - 1][i - a]) % mod;
                }
                f[i][j] = (tmp >= 0 ? tmp : tmp + mod);
            }
        if(N == 0) return f[n][m];
        if(N == 1)
        {
            int ans = 0;
            // 两条边在同一个连通块里面
            // 两条边在不同的连通块里面
            int n1 = n - 1, m2 = m - 2;
            ans = (ans + (long long) f[n1][m2] * comb[n1][2]) % mod;
            for(int i = 1; i != n1; ++i)
            {
                int tmp = 0;
                for(int j = i - 1; j <= e[i] && j <= m2; ++j)
                    tmp = (tmp + (long long) f[i][j] * f[n1 - i][m2 - j]) % mod;
                ans = (ans + (long long) tmp * i % mod * (n1 - i) % mod * comb[n1 - 1][n1 - i]) % mod;
            }
            return ans;
        }
        int ans = 0;
        // 0 和 1 之间连了一条边，于是就变成了 1 的情况了
        {
            int n2 = n - 2, m3 = m - 3;
            ans = (ans + (long long) f[n2][m3] * n2 * n2) % mod;
            for(int i = 1; i != n2; ++i)
            {
                int tmp = 0;
                for(int j = i - 1; j <= e[i] && j <= m3; ++j)
                    tmp = (tmp + (long long) f[i][j] * f[n2 - i][m3 - j]) % mod;
                ans = (ans + (long long) 2ll * tmp * i % mod * (n2 - i) % mod * comb[n2 - 1][n2 - i]) % mod;
            }
        }
        // 0 和 1 之间没有连边
        if(m >= 4)
        {
            int n2 = n - 2, m4 = m - 4;
            // 一个连通块
            ans = (ans + (long long) f[n2][m4] * comb[n2][2] * comb[n2][2]) % mod;
            
            // 两个连通块
            for(int i = 1; i != n2; ++i)
            {
                int tmp = 0;
                for(int j = i - 1; j <= e[i] && j <= m4; ++j)
                    tmp = (tmp + (long long) f[i][j] * f[n2 - i][m4 - j]) % mod;
                
                // 1. 只有一个点横跨两个连通块
                int coef_1 = 0, coef_2 = 0;
                // 考虑另一个点的两端可以怎么选择
                coef_1 = (comb[i][2] + comb[n2 - i][2]) * 2 * i * (n2 - i) % mod;
                
                // 2. 两个点都横跨两个连通块
                coef_2 = i * (n2 - i) * i * (n2 - i) % mod;
                
                ans = (ans + (long long) tmp * comb[n2 - 1][i - 1] % mod * (coef_1 + coef_2)) % mod;
            }
            // 三个连通块
            for(int A = 1; A < n2; ++A)
                for(int B = 1; A + B < n2; ++B)
                {
                    int C = n2 - A - B;
                    int split = (long long) comb[n2 - 1][A + B] * comb[A + B][A] % mod;
                    int tmp = 0;
                    for(int x = A - 1; x <= e[A] && x <= m4; ++x)
                        for(int y = B - 1; y <= e[B] && x + y <= m4; ++y)
                            tmp = (tmp + (long long) f[A][x] * f[B][y] % mod * f[C][m4 - x - y]) % mod;
                    int coef = 0;
                    (coef += A * A * B * C) %= mod;
                    (coef += A * B * B * C) %= mod;
                    (coef += A * B * C * C) %= mod;
                    ans = (ans + (long long) split * tmp % mod * coef) % mod;
                }
        }
        return ans;
    }
}	user;
