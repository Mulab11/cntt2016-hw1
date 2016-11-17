#include <algorithm>
#include <string>
#include <vector>

class BoundedOptimization {
  public:
    double maxValue(std::vector<std::string> expr, std::vector<int> lowerBound, std::vector<int> upperBound, int maxSum);
};

double BoundedOptimization::maxValue(std::vector<std::string> expr, std::vector<int> lowerBound, std::vector<int> upperBound, int maxSum)
{
    int n = lowerBound.size();
    std::vector<int> a(n);
    std::string s;
    for (const auto &x : expr) {
        s += x;
    }
    for (int i = 0; i < (int)s.length(); i += 3) {
        int x = s[i] - 'a';
        int y = s[i + 1] - 'a';
        a[x] |= 1 << y;
        a[y] |= 1 << x;
    }
    std::vector<int> sumlow(1 << n);
    std::vector<int> sumupp(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                sumlow[i] += lowerBound[j];
                sumupp[i] += upperBound[j];
            }
        }
    }
    std::vector<std::vector<int>> bvallow(1 << n, std::vector<int>(n));
    std::vector<std::vector<int>> bvalupp(1 << n, std::vector<int>(n));
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                for (int k = 0; k < n; k++) {
                    if ((a[j] >> k) & 1) {
                        bvallow[i][k] += lowerBound[j];
                        bvalupp[i][k] += upperBound[j];
                    }
                }
            }
        }
    }
    int ss = std::min(sumupp[(1 << n) - 1], maxSum);
    double ans = 0;
    // Enumerate the variables that have value == lower bound
    for (int i = 0; i < (1 << n); i++) {
        int rem = ~i & ((1 << n) - 1);
        // Enumerate the variables that have value == upper bound
        for (int j = rem; j >= 0; j = j ? (j - 1) & rem : -1) {
            int u = ~i & ~j & ((1 << n) - 1);
            bool ok = true;
            for (int k = 0; k < n; k++) {
                if (((u >> k) & 1) && (~a[k] & u) != (1 << k)) {
                    // Skip if the remaining variables does not form a
                    // clique. If there is no xy term in expr, it is
                    // always possible to make either x or y reach bound
                    // value without making answer worse.
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                continue;
            }
            int usum = ss - sumlow[i] - sumupp[j];
            if (usum < sumlow[u] || usum > sumupp[u]) {
                continue;
            }
            std::vector<int> bv(n);
            for (int k = 0; k < n; k++) {
                bv[k] = bvallow[i][k] + bvalupp[j][k];
            }
            int curans2 = usum * usum;
            for (int k = 0; k < n; k++) {
                if ((i >> k) & 1) {
                    curans2 += bv[k] * lowerBound[k];
                }
                if ((j >> k) & 1) {
                    curans2 += bv[k] * upperBound[k];
                }
            }
            int ubs = 0;
            int ucnt = 0;
            for (int k = 0; k < n; k++) {
                if ((u >> k) & 1) {
                    ubs += bv[k];
                    ucnt++;
                }
            }
            int cd = ucnt;
            long long sn = 0;
            long long sd = 2 * ucnt * ucnt;
            for (int k = 0; k < n; k++) {
                if ((u >> k) & 1) {
                    int cn = bv[k] * ucnt - ubs + usum;
                    if (cn < cd * lowerBound[k] || cn > cd * upperBound[k]) {
                        // The optimal solution falls out of bound
                        ok = false;
                        break;
                    }
                    sn += (long long)cn * (2 * bv[k] * cd - cn);
                }
            }
            if (!ok) {
                continue;
            }
            sn += (long long)curans2 * (sd / 2);
            ans = std::max(ans, (double)sn / sd);
        }
    }
    return ans;
}
