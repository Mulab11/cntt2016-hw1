#include <algorithm>
#include <string>
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

class ColorfulBuilding {
  public:
    int count(std::vector<std::string> color1, std::vector<std::string> color2, int L);

  private:
    static const int MOD = 1000000009;

    std::vector<int> fac;
    std::vector<int> faci;

    void initFactorial(int n);
};

int ColorfulBuilding::count(std::vector<std::string> color1, std::vector<std::string> color2, int L)
{
    std::string s1;
    for (const auto &x : color1) {
        s1 += x;
    }
    std::string s2;
    for (const auto &x : color2) {
        s2 += x;
    }
    int n = s1.length();
    std::vector<std::pair<char, char>> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = std::make_pair(s1[i], s2[i]);
    }
    std::vector<std::pair<char, char>> cr = c;
    std::sort(cr.begin(), cr.end());
    cr.erase(std::unique(cr.begin(), cr.end()), cr.end());
    int coln = cr.size();
    std::vector<int> col(n);
    for (int i = 0; i < n; i++) {
        col[i] = std::lower_bound(cr.begin(), cr.end(), c[i]) - cr.begin();
    }
    initFactorial(n);
    // If visible buildings are a1, a2, ..., ak, N, the number of ways
    // to insert the remaining buildings is (N-1)! / product(N - ai)
    // f[i] = number of ways to get i color blocks with the current
    // suffix
    std::vector<int> f(L + 1);
    // fs[i] = sum of f[i] * faci[n - p] for all previous suffices p
    std::vector<int> fs(L + 1);
    // fcols[i][j] = sum of f[j] * faci[n - p] for all previous suffices
    // p with color i
    std::vector<std::vector<int>> fcols(coln, std::vector<int>(L + 1));
    f[0] = 1;
    fs[0] = 1;
    fcols[col[n - 1]][0] = 1;
    for (int i = n - 1; i >= 0; i--) {
        // For all suffices
        f[0] = 0;
        for (int k = 1; k <= L; k++) {
            f[k] = (long long)fs[k - 1] * fac[n - i - 1] % MOD;
        }
        if (i) {
            // Work with suffices with the same color
            for (int k = 1; k <= L; k++) {
                f[k] = (f[k] - (long long)fcols[col[i - 1]][k - 1] * fac[n - i - 1] % MOD + MOD) % MOD;
            }
            for (int k = 0; k <= L; k++) {
                f[k] = (f[k] + (long long)fcols[col[i - 1]][k] * fac[n - i - 1]) % MOD;
            }
        }
        for (int j = 0; j <= L; j++) {
            fs[j] = (fs[j] + (long long)f[j] * faci[n - i]) % MOD;
        }
        if (i > 0) {
            for (int j = 0; j <= L; j++) {
                fcols[col[i - 1]][j] = (fcols[col[i - 1]][j] + (long long)f[j] * faci[n - i]) % MOD;
            }
        }
    }
    return f[L];
}

void ColorfulBuilding::initFactorial(int n)
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
