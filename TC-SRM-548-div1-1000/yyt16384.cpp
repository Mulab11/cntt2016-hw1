#include <algorithm>
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

class KingdomAndCities {
  public:
    int howMany(int N, int M, int K);

  private:
    static const int MOD = 1000000007;

    std::vector<int> fac;
    std::vector<int> faci;
    std::vector<std::vector<int>> cnt1;
    std::vector<std::vector<int>> cnt2;
    std::vector<std::vector<int>> cnt3;
    std::vector<std::vector<int>> cnt22;

    void initFactorial(int n);
    int binomial(int x, int y);
    void initGraphCount1(int n, int k);
    void initGraphCount2(int n, int k);
    void initGraphCount3(int n, int k);
    void initGraphCount22(int n, int k);
};

int KingdomAndCities::howMany(int N, int M, int K)
{
    initFactorial((N + 2) * (N + 1) / 2);
    initGraphCount1(N, K);
    initGraphCount2(N, K);
    initGraphCount3(N, K);
    initGraphCount22(N, K);
    if (M == 0) {
        return cnt1[N][K];
    } else if (M == 1) {
        int s1 = N >= 3 && K >= 2 ? (long long)cnt2[N - 2][K - 2] * (N - 1) * (N - 2) / 2 % MOD : 0;
        return s1;
    } else {
        int s1 = N >= 4 && K >= 4 ? (long long)cnt2[N - 3][K - 4] * (N - 2) * (N - 3) / 2 % MOD : 0;
        int s2 = N >= 5 && K >= 4 ? (long long)cnt3[N - 4][K - 4] * (N - 2) * (N - 3) * (N - 4) % MOD : 0;
        int s3 = N >= 6 && K >= 4 ? (long long)cnt22[N - 4][K - 4] * (N - 2) * (N - 3) * (N - 4) * (N - 5) / 4 % MOD : 0;
        int s4 = N >= 3 && K >= 3 ? (long long)cnt1[N - 2][K - 3] * (N - 2) % MOD : 0;
        int s5 = N >= 4 && K >= 3 ? (long long)cnt2[N - 3][K - 3] * (N - 2) * (N - 3) % MOD : 0;
        return ((long long)s1 + s2 + s3 + s4 + s5) % MOD;
    }
}

void KingdomAndCities::initFactorial(int n)
{
    fac.resize(n + 1);
    faci.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = (long long)fac[i - 1] * i % MOD;
    }
    faci[n] = powermod(fac[n], MOD - 2, MOD);
    for (int i = n; i >= 1; i--) {
        faci[i - 1] = (long long)faci[i] * i % MOD;
    }
}

int KingdomAndCities::binomial(int x, int y)
{
    return (long long)fac[x] * faci[y] % MOD * faci[x - y] % MOD;
}

void KingdomAndCities::initGraphCount1(int n, int k)
{
    // cnt1[i][j] = number of connected graphs with n nodes and k edges
    cnt1.clear();
    cnt1.resize(n + 1, std::vector<int>(k + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j <= k && j <= i * (i - 1) / 2; j++) {
            int s = binomial(i * (i - 1) / 2, j);
            // Remove the unconnected cases by enumerating the size of
            // the connected component with the first node
            for (int p = 1; p < i; p++) {
                for (int q = std::max(p - 1, j - (i - p) * (i - p - 1) / 2); q <= j && q <= p * (p - 1) / 2; q++) {
                    int u = (long long)binomial(i - 1, p - 1) * cnt1[p][q] % MOD * binomial((i - p) * (i - p - 1) / 2, j - q) % MOD;
                    s = (s - u + MOD) % MOD;
                }
            }
            cnt1[i][j] = s;
        }
    }
}

void KingdomAndCities::initGraphCount2(int n, int k)
{
    // cnt2[i][j] = number of connected graphs with n nodes and k edges
    // where the first node has size 2
    cnt2.clear();
    cnt2.resize(n + 1, std::vector<int>(k + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j <= k && j <= (i + 1) * i / 2; j++) {
            int s = binomial((i + 1) * i / 2, j);
            // Remove the unconnected cases by enumerating the size of
            // the connected component with the first node
            for (int p = 1; p < i; p++) {
                for (int q = std::max(p - 1, j - (i - p) * (i - p - 1) / 2); q <= j && q <= (p + 1) * p / 2; q++) {
                    int u = (long long)binomial(i - 1, p - 1) * cnt2[p][q] % MOD * binomial((i - p) * (i - p - 1) / 2, j - q) % MOD;
                    s = (s - u + MOD) % MOD;
                }
            }
            cnt2[i][j] = s;
        }
    }
}

void KingdomAndCities::initGraphCount3(int n, int k)
{
    // cnt3[i][j] = number of connected graphs with n nodes and k edges
    // where the first node has size 3
    cnt3.clear();
    cnt3.resize(n + 1, std::vector<int>(k + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j <= k && j <= (i + 2) * (i + 1) / 2; j++) {
            int s = binomial((i + 2) * (i + 1) / 2, j);
            // Remove the unconnected cases by enumerating the size of
            // the connected component with the first node
            for (int p = 1; p < i; p++) {
                for (int q = std::max(p - 1, j - (i - p) * (i - p - 1) / 2); q <= j && q <= (p + 2) * (p + 1) / 2; q++) {
                    int u = (long long)binomial(i - 1, p - 1) * cnt3[p][q] % MOD * binomial((i - p) * (i - p - 1) / 2, j - q) % MOD;
                    s = (s - u + MOD) % MOD;
                }
            }
            cnt3[i][j] = s;
        }
    }
}

void KingdomAndCities::initGraphCount22(int n, int k)
{
    // cnt22[i][j] = number of connected graphs with n nodes and k edges
    // where the first two nodes have size 2
    cnt22.clear();
    cnt22.resize(n + 1, std::vector<int>(k + 1));
    for (int i = 2; i <= n; i++) {
        for (int j = i - 1; j <= k && j <= (i + 2) * (i + 1) / 2; j++) {
            int s = binomial((i + 2) * (i + 1) / 2, j);
            // Remove the unconnected cases by enumerating the size of
            // the connected component with the first node
            for (int p = 2; p < i; p++) {
                for (int q = std::max(p - 1, j - (i - p) * (i - p - 1) / 2); q <= j && q <= (p + 2) * (p + 1) / 2; q++) {
                    int u = (long long)binomial(i - 2, p - 2) * cnt22[p][q] % MOD * binomial((i - p) * (i - p - 1) / 2, j - q) % MOD;
                    s = (s - u + MOD) % MOD;
                }
            }
            for (int p = 1; p < i; p++) {
                for (int q = std::max(p - 1, j - (i - p + 1) * (i - p) / 2); q <= j && q <= (p + 1) * p / 2; q++) {
                    int u = (long long)binomial(i - 2, p - 1) * cnt2[p][q] % MOD * binomial((i - p + 1) * (i - p) / 2, j - q) % MOD;
                    s = (s - u + MOD) % MOD;
                }
            }
            cnt22[i][j] = s;
        }
    }
}
