#include <algorithm>
#include <vector>

static const int INF = 0x3f3f3f3f;

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

class WolfPack {
  public:
    int calc(std::vector<int> x, std::vector<int> y, int m);

  private:
    static const int MOD = 1000000007;

    std::vector<int> fac;
    std::vector<int> faci;

    void initFactorial(int n);
    int binomial(int x, int y);
    int calcOneDimension(const std::vector<int> &a, int m);
};

int WolfPack::calc(std::vector<int> x, std::vector<int> y, int m)
{
    initFactorial(m);
    int n = x.size();
    std::vector<int> u(n);
    std::vector<int> v(n);
    for (int i = 0; i < n; i++) {
        u[i] = x[i] + y[i];
        v[i] = x[i] - y[i];
    }
    for (int i = 1; i < n; i++) {
        if ((u[i] % 2 != 0) != (u[0] % 2 != 0)) {
            // Different parity, impossible to meet at one point
            return 0;
        }
    }
    return (long long)calcOneDimension(u, m) * calcOneDimension(v, m) % MOD;
}

void WolfPack::initFactorial(int n)
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

int WolfPack::binomial(int x, int y)
{
    return (long long)fac[x] * faci[y] % MOD * faci[x - y] % MOD;
}

int WolfPack::calcOneDimension(const std::vector<int> &a, int m)
{
    int l = -INF;
    int r = INF;
    for (auto x : a) {
        l = std::max(l, x - m);
        r = std::min(r, x + m);
    }
    int ans = 0;
    // Enumerate the meeting point
    for (int i = l; i <= r; i++) {
        if ((i % 2 != 0) == ((a[0] + m) % 2 != 0)) {
            int s = 1;
            for (auto x : a) {
                int cntl = (x + m - i) / 2;
                s = (long long)s * binomial(m, cntl) % MOD;
            }
            ans = (ans + s) % MOD;
        }
    }
    return ans;
}
