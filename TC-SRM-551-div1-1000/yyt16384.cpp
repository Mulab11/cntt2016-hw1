#include <algorithm>
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

class SweetFruits {
  public:
    int countTrees(std::vector<int> sweetness, int maxSweetness);

  private:
    static const int MOD = 1000000007;

    std::vector<int> fac;
    std::vector<int> faci;

    void initFactorial(int n);
    int binomial(int x, int y);
    int determinant(std::vector<std::vector<int>> f);
};

int SweetFruits::countTrees(std::vector<int> sweetness, int maxSweetness)
{
    std::vector<int> a;
    int cntbitter = 0;
    for (auto x : sweetness) {
        if (x >= 0) {
            a.push_back(x);
        } else {
            cntbitter++;
        }
    }
    int n = a.size();
    initFactorial(n);
    // f[i] = number of trees with i sweet nodes not adjacent to any
    // other sweet nodes
    std::vector<int> f(n + 1);
    for (int i = 0; i <= n; i++) {
        std::vector<std::vector<int>> g(n + cntbitter - 1, std::vector<int>(n + cntbitter - 1));
        for (int j = 0; j < n + cntbitter; j++) {
            for (int k = j + 1; k < n + cntbitter; k++) {
                if (j >= i || k >= n) {
                    if (k < n + cntbitter - 1) {
                        g[j][k] = MOD - 1;
                        g[k][j] = MOD - 1;
                        g[k][k]++;
                    }
                    g[j][j]++;
                }
            }
        }
        f[i] = determinant(g);
    }
    for (int i = n; i >= 0; i--) {
        for (int j = i + 1; j <= n; j++) {
            f[i] = (f[i] - (long long)f[j] * binomial(n - i, j - i) % MOD + MOD) % MOD;
        }
    }
    int hf = n / 2;
    // sl[i] = possible sums of i elements chosen from the first hf
    // elements
    std::vector<std::vector<int>> sl(hf + 1);
    for (int i = 0; i < (1 << hf); i++) {
        int cnt = 0;
        int sum = 0;
        for (int j = 0; j < hf; j++) {
            if ((i >> j) & 1) {
                cnt++;
                sum += a[j];
            }
        }
        sl[cnt].push_back(sum);
    }
    for (auto &x : sl) {
        std::sort(x.begin(), x.end());
    }
    // sr[i] = possible sums of i elements chosen from the last n - hf
    // elements
    std::vector<std::vector<int>> sr(n - hf + 1);
    for (int i = 0; i < (1 << (n - hf)); i++) {
        int cnt = 0;
        int sum = 0;
        for (int j = 0; j < n - hf; j++) {
            if ((i >> j) & 1) {
                cnt++;
                sum += a[j + hf];
            }
        }
        sr[cnt].push_back(sum);
    }
    for (auto &x : sr) {
        std::sort(x.begin(), x.end());
    }
    // cnts[i] = number of subsets with i elements and total sum <=
    // maxSweetness
    std::vector<int> cnts(n + 1);
    for (int i = 0; i <= hf; i++) {
        for (int j = 0; j <= n - hf; j++) {
            int k = sr[j].size();
            for (auto x : sl[i]) {
                while (k >= 1 && x + sr[j][k - 1] > maxSweetness) {
                    k--;
                }
                cnts[i + j] = (cnts[i + j] + k) % MOD;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = (ans + (long long)f[n - i] * cnts[i]) % MOD;
    }
    return ans;
}

void SweetFruits::initFactorial(int n)
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

int SweetFruits::binomial(int x, int y)
{
    return (long long)fac[x] * faci[y] % MOD * faci[x - y] % MOD;
}

int SweetFruits::determinant(std::vector<std::vector<int>> f)
{
    int s = 1;
    for (int i = 0; i < (int)f.size(); i++) {
        int r = -1;
        for (int j = i; j < (int)f.size(); j++) {
            if (f[j][i]) {
                r = j;
                break;
            }
        }
        if (r == -1) {
            return 0;
        }
        std::swap(f[i], f[r]);
        s = (long long)s * f[i][i] % MOD;
        int tmp = powermod(f[i][i], MOD - 2, MOD);
        for (int j = i; j < (int)f.size(); j++) {
            f[i][j] = (long long)f[i][j] * tmp % MOD;
        }
        for (int j = i + 1; j < (int)f.size(); j++) {
            tmp = f[j][i];
            for (int k = i; k < (int)f.size(); k++) {
                f[j][k] = (f[j][k] - (long long)f[i][k] * tmp % MOD + MOD) % MOD;
            }
        }
    }
    return s;
}
