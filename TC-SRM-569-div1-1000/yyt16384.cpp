#include <utility>
#include <vector>

static int powermod(int x, int y, int m)
{
    int s = 1;
    while (y) {
        if (y & 1) {
            s = (long long)s * x % m;
        }
        x = (long long)x * x % m;
        y >>= 1;
    }
    return s;
}

class MegaFactorial {
  public:
    int countTrailingZeros(int N, int K, int B);

  private:
    static const int MOD = 1000000009;

    int countPrimeFactorsModulo(int n, int k, int p, int mod);
    std::vector<std::vector<int>> matrixMultiplication(const std::vector<std::vector<int>> &x, const std::vector<std::vector<int>> &y, int mod);
};

int MegaFactorial::countTrailingZeros(int N, int K, int B)
{
    int u = B;
    int p = -1;
    int cnt = -1;
    for (int i = 2; i <= u; i++) {
        if (u % i == 0) {
            int c = 0;
            while (u % i == 0) {
                u /= i;
                c++;
            }
            if (u == 1) {
                p = i;
                cnt = c;
            }
        }
    }
    int s = (countPrimeFactorsModulo(N, K, p, MOD) - countPrimeFactorsModulo(N, K, p, cnt) + MOD) % MOD;
    // For B <= 10, we can assume that the answer only depends on the
    // count of maximum prime factor, as there can't be any factor
    // p1^c1*p2^c2 with p1 < p2 and c1 > c2
    return (long long)s * powermod(cnt, MOD - 2, MOD) % MOD;
}

int MegaFactorial::countPrimeFactorsModulo(int n, int k, int p, int mod)
{
    std::vector<std::vector<int>> g(k + 1, std::vector<int>(k + 1));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j <= i; j++) {
            g[i][j] = 1 % mod;
        }
    }
    g[k][k] = 1 % mod;
    std::vector<std::vector<int>> x = g;
    std::vector<std::vector<int>> s(k + 1, std::vector<int>(k + 1));
    for (int i = 0; i <= k; i++) {
        s[i][i] = 1 % mod;
    }
    int u = n;
    while (u) {
        for (int i = 0; i < u % p; i++) {
            s = matrixMultiplication(s, x, mod);
        }
        std::vector<std::vector<int>> y = x;
        for (int i = 0; i < p - 1; i++) {
            y = matrixMultiplication(y, x, mod);
        }
        // Add a prime factor p every p^c numbers
        for (int i = 0; i < k; i++) {
            y[i][k] = (y[i][k] + 1) % mod;
        }
        x = std::move(y);
        u /= p;
    }
    return s[k - 1][k];
}

std::vector<std::vector<int>> MegaFactorial::matrixMultiplication(const std::vector<std::vector<int>> &x, const std::vector<std::vector<int>> &y, int mod)
{
    std::vector<std::vector<int>> z(x.size(), std::vector<int>(y[0].size()));
    for (int i = 0; i < (int)x.size(); i++) {
        for (int j = 0; j < (int)y[0].size(); j++) {
            for (int k = 0; k < (int)x[0].size(); k++) {
                z[i][j] = (z[i][j] + (long long)x[i][k] * y[k][j]) % mod;
            }
        }
    }
    return z;
}
