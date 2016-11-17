#include <string>
#include <vector>

class RandomPaintingOnABoard {
  public:
    double expectedSteps(std::vector<std::string> prob);

  private:
    double expectedSteps2(const std::vector<std::vector<int>> &a);
    std::vector<int> inclusionExclusionDP(const std::vector<int> &a);
};

double RandomPaintingOnABoard::expectedSteps(std::vector<std::string> prob)
{
    int n = prob.size();
    int m = prob[0].length();
    std::vector<std::vector<int>> a;
    if (n < m) {
        a.resize(n, std::vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i][j] = prob[i][j] - '0';
            }
        }
    } else {
        a.resize(m, std::vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = prob[j][i] - '0';
            }
        }
    }
    return expectedSteps2(a);
}

double RandomPaintingOnABoard::expectedSteps2(const std::vector<std::vector<int>> &a)
{
    int n = a.size();
    int m = a[0].size();
    std::vector<int> colsum(m);
    for (const auto &x : a) {
        for (int i = 0; i < m; i++) {
            colsum[i] += x[i];
        }
    }
    int allsum = 0;
    for (auto x : colsum) {
        allsum += x;
    }
    // Using inclusion-exclusion, enumerate the chosen rows
    double ans = 0;
    for (int i = 0; i < (1 << n); i++) {
        int fl = -1;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                fl *= -1;
            }
        }
        std::vector<int> u = colsum;
        int ds = 0;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                for (int k = 0; k < m; k++) {
                    u[k] -= a[j][k];
                    ds += a[j][k];
                }
            }
        }
        std::vector<int> f = inclusionExclusionDP(u);
        for (int j = 0; j < (int)f.size(); j++) {
            int del = ds + j;
            if (!del) {
                // Choosing no sets, skipping
                continue;
            }
            // Probability of not filling chosen rows and columns in one
            // turn is p = (allsum - del) / allsum, so it contributes
            // sum(p ** k, k >= 0) = 1 / (1 - p) to answer
            ans += (double)allsum / del * f[j] * fl;
        }
    }
    return ans;
}

std::vector<int> RandomPaintingOnABoard::inclusionExclusionDP(const std::vector<int> &a)
{
    std::vector<int> f = {1};
    for (auto x : a) {
        f.resize(f.size() + x);
        for (int i = f.size() - 1; i >= x; i--) {
            f[i] -= f[i - x];
        }
    }
    return f;
}
