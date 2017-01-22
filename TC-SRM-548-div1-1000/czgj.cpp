#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int p = 1000000007;
int f[55][55], C[2505][2505];
class KingdomAndCities {
    public:
    int F(int i, int j) {if (i < 0 || j < 0) return 0; else return f[i][j];}
    int howMany(int N, int M, int K) {
        for (int i = 0; i <= N * N; ++i) {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; ++j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
        }
        for (int i = 1; i <= N; ++i)
            for (int j = 0; j <= K; ++j) {
                f[i][j] = C[i * (i - 1) / 2][j];
                for (int k = 1; k < i; ++k)
                    for (int l = 0; l <= j; ++l)
                        f[i][j] = (f[i][j] - 1ll * C[i - 1][k - 1] * f[k][l] % p * C[(i - k) * (i - k - 1) / 2][j - l] % p) % p;
                (f[i][j] += p) %= p;
            }
        if (!M) return f[N][K];
        if (M == 1) return ((K - 1ll) * F(N - 1, K - 1) % p + (K - 2ll) * F(N - 1, K - 2) % p) % p;
        else {
            int ans = (K - 2ll) * F(N - 2, K - 2) % p * 2 % p;
            ans = (ans + (K - 3ll) * F(N - 2, K - 3) % p * 2 % p) % p;
            ans = (ans + (N - 2ll) * F(N - 2, K - 3) % p) % p;
            ans = (ans + (K - 2ll) * (K - 3) * F(N - 2, K - 2) % p) % p;
            ans = (ans + (K - 3ll) * F(N - 2, K - 3) % p) % p;
            ans = (ans + (K - 3ll) * (K - 4) * 2 * F(N - 2, K - 3) % p) % p;
            ans = (ans + (K - 4ll) * (K - 4) * F(N - 2, K - 4) % p) % p;
            return ans;
        }
    }
};
