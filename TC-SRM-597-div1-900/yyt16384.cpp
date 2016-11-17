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

class LittleElephantAndBoard {
  public:
    int getNumber(int M, int R, int G, int B);

  private:
    static const int MOD = 1000000007;

    std::vector<int> fac;
    std::vector<int> faci;

    void initFactorial(int n);
    int binomial(int x, int y);
    int count(int n, int x, int y);
};

int LittleElephantAndBoard::getNumber(int M, int R, int G, int B)
{
    initFactorial(M);
    // The board can be constructed from the sequence of colors that are
    // missing in each column
    int r = M - R;
    int g = M - G;
    int b = M - B;
    // The red colors split the sequence into parts, and count the
    // number of ways to put green and blue colors in the spaces
    int ans = ((long long)count(r + 1, g, b) + 2 * count(r, g, b) + count(r - 1, g, b)) % MOD;
    return 2 * ans % MOD;
}

void LittleElephantAndBoard::initFactorial(int n)
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

int LittleElephantAndBoard::binomial(int x, int y)
{
    return (long long)fac[x] * faci[y] % MOD * faci[x - y] % MOD;
}

int LittleElephantAndBoard::count(int n, int x, int y)
{
    if (n < 0 || x < 0 || y < 0) {
        return 0;
    }
    int ans = 0;
    // Enumerate the number of parts that have odd number of items
    for (int i = (x + y) % 2; i <= n; i += 2) {
        // The number of parts that have fewer x-items than y-items
        int kx = (y - x + i) / 2;
        // The number of parts that have fewer y-items than x-items
        int ky = i - kx;
        if (kx < 0 || ky < 0) {
            continue;
        }
        // Number of ways to choose the parts with odd number of items
        int s = (long long)binomial(n, kx) * binomial(n - kx, ky) % MOD;
        // Every part with even number of items can be constructed in 2
        // ways
        s = (long long)s * powermod(2, n - i, MOD) % MOD;
        int p = x + kx;
        if (p < n) {
            continue;
        }
        // Put p unlabeled items into n labeled parts
        s = (long long)s * binomial(p - 1, n - 1) % MOD;
        ans = (ans + s) % MOD;
    }
    return ans;
}
