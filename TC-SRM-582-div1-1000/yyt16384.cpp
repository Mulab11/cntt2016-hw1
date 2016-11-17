#include <cmath>
#include <utility>
#include <vector>

class SemiPerfectPower {
  public:
    long long count(long long L, long long R);

  private:
    std::vector<char> issqf;
    std::vector<std::vector<int>> sqfcntmul;
    std::vector<char> iscbf;
    std::vector<std::vector<int>> cbfpdlist;
    std::vector<int> cbfprod1;
    std::vector<int> cbfprod2;

    void initSquareFree(int n);
    void initCubeFree(int n);
    void initSquareFreeCount(int n, long long R);
    long long count2(long long n);
    long long countSemiSquare(long long n);
    long long countSemiCube(long long n);
    long long countSemiSquareAndSemiCube(long long n);
};

long long SemiPerfectPower::count(long long L, long long R)
{
    initSquareFree((int)std::cbrt(R) + 1);
    initCubeFree((int)std::pow(R, 1.0 / 4) + 1);
    initSquareFreeCount((int)std::pow(R, 1.0 / 4) + 1, R);
    return count2(R) - count2(L - 1);
}

void SemiPerfectPower::initSquareFree(int n)
{
    issqf.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int x = i;
        bool sqf = true;
        for (int j = 2; j * j * j <= x; j++) {
            if (x % j == 0) {
                x /= j;
                if (x % j == 0) {
                    sqf = false;
                    break;
                }
            }
        }
        if (x > 1) {
            int k = std::sqrt(x) + 0.5;
            if (k * k == x) {
                sqf = false;
            }
        }
        issqf[i] = sqf;
    }
}

void SemiPerfectPower::initCubeFree(int n)
{
    iscbf.resize(n + 1);
    cbfpdlist.resize(n + 1);
    cbfprod1.resize(n + 1);
    cbfprod2.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int x = i;
        bool cbf = true;
        std::vector<int> p1;
        int prod1 = 1;
        int prod2 = 1;
        for (int j = 2; j * j <= x; j++) {
            if (x % j == 0) {
                int cnt = 0;
                while (x % j == 0) {
                    x /= j;
                    cnt++;
                }
                if (cnt >= 3) {
                    cbf = false;
                    break;
                }
                if (cnt == 1) {
                    p1.push_back(j);
                    prod1 *= j;
                } else {
                    prod2 *= j;
                }
            }
        }
        if (x > 1) {
            p1.push_back(x);
            prod1 *= x;
        }
        if (cbf) {
            std::vector<int> pdlist = {1};
            pdlist.reserve(1 << p1.size());
            for (auto p : p1) {
                int m = pdlist.size();
                for (int k = 0; k < m; k++) {
                    pdlist.push_back(pdlist[k] * p);
                }
            }
            iscbf[i] = true;
            cbfpdlist[i] = std::move(pdlist);
            cbfprod1[i] = prod1;
            cbfprod2[i] = prod2;
        }
    }
}

void SemiPerfectPower::initSquareFreeCount(int n, long long R)
{
    sqfcntmul.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        if (issqf[i]) {
            int m = std::cbrt(R / i / i / i / i) + 1;
            sqfcntmul[i].resize(m + 1);
            for (int j = 1; j <= m; j++) {
                sqfcntmul[i][j] = sqfcntmul[i][j - 1] + issqf[j * i];
            }
        }
    }
}

long long SemiPerfectPower::count2(long long n)
{
    // Every semi-perfect power with c >= 4 is also a semi-square
    return countSemiSquare(n) + countSemiCube(n) - countSemiSquareAndSemiCube(n);
}

long long SemiPerfectPower::countSemiSquare(long long n)
{
    long long ans = 0;
    // Enumerate a, a^3 < a*b^2 <= n
    for (int i = 1; (long long)i * i * i < n; i++) {
        if (issqf[i]) {
            int k = std::sqrt(n / i) - 1;
            while ((long long)i * (k + 1) * (k + 1) <= n) {
                k++;
            }
            ans += k - i;
        }
    }
    return ans;
}

long long SemiPerfectPower::countSemiCube(long long n)
{
    long long ans = 0;
    // Enumerate a, a^4 < a*b^3 <= n
    for (int i = 1; (long long)i * i * i * i < n; i++) {
        if (iscbf[i]) {
            int k = std::cbrt(n / i) - 1;
            while ((long long)i * (k + 1) * (k + 1) * (k + 1) <= n) {
                k++;
            }
            ans += k - i;
        }
    }
    return ans;
}

long long SemiPerfectPower::countSemiSquareAndSemiCube(long long n)
{
    // a*b^2 = c*d^3, a < b, c < d
    // Extract square parts of d and cube parts of b, getting
    // a*b^2*e^6 = c*d^3*e^6, a < b*e^3, c < d*e^2
    // Where a and d are square-free, b and c are cube-free
    long long ans = 0;
    // Enumerate e
    for (int e = 1; (long long)e * e * e * e * e * e <= n; e++) {
        // Enumerate c
        for (int c = 1; (long long)c * c * c * c < n && (long long)c * e * e * e * e * e * e <= n; c++) {
            if (iscbf[c]) {
                // For every prime factor that appears in c once, it
                // will add this prime factor once to a
                // For every prime factor that appears in c twice, it
                // will add this prime factor once to b
                // For every prime factor in d, if it appears in c for 0
                // or 2 times, it will add this prime factor once to a
                // and b, thus not changing the condition a < b*e^3. If
                // it appears in c once, it will remove this prime
                // factor from a and add it to b twice, thus multiplying
                // the RHS by p^3
                // Range limits of d
                int dl = c / e / e;
                long long dr3 = n / e / e / e / e / e / e / c;
                int dr = std::cbrt(dr3) - 1;
                while ((long long)(dr + 1) * (dr + 1) * (dr + 1) <= dr3) {
                    dr++;
                }
                std::vector<int> ss(cbfpdlist[c].size());
                for (int i = 0; i < (int)cbfpdlist[c].size(); i++) {
                    int pd = cbfpdlist[c][i];
                    ss[i] = sqfcntmul[pd][dr / pd] - sqfcntmul[pd][dl / pd];
                }
                for (int i = cbfpdlist[c].size() - 1; i >= 0; i--) {
                    for (int j = i; j != 0; j = (j - 1) & i) {
                        ss[i & ~j] -= ss[i];
                    }
                }
                // Enumerate the set of prime factors that will multiply
                // RHS by p^3
                for (int i = 0; i < (int)cbfpdlist[c].size(); i++) {
                    int pd = cbfpdlist[c][i];
                    if (cbfprod1[c] < (long long)cbfprod2[c] * pd * pd * pd * e * e * e) {
                        ans += ss[i];
                    }
                }
            }
        }
    }
    return ans;
}
