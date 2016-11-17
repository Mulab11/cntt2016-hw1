#include <algorithm>
#include <vector>

class AstronomicalRecords {
  public:
    int minimalPlanets(std::vector<int> A, std::vector<int> B);

  private:
    int LCS(const std::vector<int> &A, const std::vector<int> &B, int x, int y);
};

int AstronomicalRecords::minimalPlanets(std::vector<int> A, std::vector<int> B)
{
    int ans = A.size() + B.size();
    // Enumerate the ratio
    for (auto x : A) {
        for (auto y : B) {
            ans = std::min<int>(ans, A.size() + B.size() - LCS(A, B, x, y));
        }
    }
    return ans;
}

int AstronomicalRecords::LCS(const std::vector<int> &A, const std::vector<int> &B, int x, int y)
{
    int n = A.size();
    int m = B.size();
    std::vector<std::vector<int>> f(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((long long)A[i] * y == (long long)B[j] * x) {
                f[i][j] = (i && j ? f[i - 1][j - 1] : 0) + 1;
            } else {
                f[i][j] = std::max(i ? f[i - 1][j] : 0, j ? f[i][j - 1] : 0);
            }
        }
    }
    return f[n - 1][m - 1];
}
