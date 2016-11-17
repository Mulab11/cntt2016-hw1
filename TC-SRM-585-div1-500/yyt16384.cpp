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

class LISNumber {
  public:
    int count(std::vector<int> cardsnum, int K);

  private:
    static const int MOD = 1000000007;
};

int LISNumber::count(std::vector<int> cardsnum, int K)
{
    // f[i] = number of ways to order selected cards to get a LISNumber
    // of i
    std::vector<int> f(K + 1);
    f[0] = 1;
    int cur = 0;
    for (auto x : cardsnum) {
        for (int i = 0; i < x; i++) {
            std::vector<int> g(K + 1);
            for (int j = i; j <= K; j++) {
                // Insert at the end of a increasing sequence, but not
                // after a card with the same number
                g[j] = (g[j] + (long long)f[j] * (j - i)) % MOD;
            }
            for (int j = 0; j < K; j++) {
                // Insert in other places
                g[j + 1] = (g[j + 1] + (long long)f[j] * (cur + 1 - j + i)) % MOD;
            }
            f = std::move(g);
            cur++;
        }
        int s = 1;
        for (int i = 1; i <= x; i++) {
            s = (long long)s * i % MOD;
        }
        s = powermod(s, MOD - 2, MOD);
        for (auto &p : f) {
            p = (long long)p * s % MOD;
        }
    }
    return f[K];
}
