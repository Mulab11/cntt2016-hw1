#include <algorithm>
#include <utility>
#include <vector>

class LittleElephantAndPermutationDiv1 {
  public:
    int getNumber(int N, int K);

  private:
    static const int MOD = 1000000007;
};

int LittleElephantAndPermutationDiv1::getNumber(int N, int K)
{
    // f[i][j] = Number of ways to get i positions with two values and
    // magic value of j
    std::vector<std::vector<int>> f(N + 1, std::vector<int>(K + 1));
    f[0][0] = 1;
    for (int i = 0; i < N; i++) {
        std::vector<std::vector<int>> g(N + 1, std::vector<int>(K + 1));
        for (int j = 0; j <= N; j++) {
            int p0 = N - 2 * i + j;
            int p1 = i - j;
            for (int k = 0; k <= K; k++) {
                if (f[j][k]) {
                    int t;
                    int s;
                    // Two values occupy different empty positions
                    t = std::min(k + 2 * (N - i), K);
                    s = (long long)f[j][k] * p0 % MOD * (p0 - 1) % MOD;
                    if (s) {
                        g[j][t] = (g[j][t] + s) % MOD;
                    }
                    // Two values occupy the same empty position
                    t = std::min(k + (N - i), K);
                    s = (long long)f[j][k] * p0 % MOD;
                    if (s) {
                        g[j + 1][t] = (g[j + 1][t] + s) % MOD;
                    }
                    // Only one value occupies an empty position
                    t = std::min(k + (N - i), K);
                    s = (long long)f[j][k] * p0 % MOD * p1 % MOD * 2 % MOD;
                    if (s) {
                        g[j + 1][t] = (g[j + 1][t] + s) % MOD;
                    }
                    // Neither value occupies an empty position
                    t = k;
                    s = (long long)f[j][k] * p1 % MOD * p1 % MOD;
                    if (s) {
                        g[j + 2][t] = (g[j + 2][t] + s) % MOD;
                    }
                }
            }
        }
        f = std::move(g);
    }
    return f[N][K];
}
