#include <string>
#include <utility>
#include <vector>

class TheExperiment {
  public:
    int countPlacements(std::vector<std::string> intensity, int M, int L, int A, int B);

  private:
    static const int MOD = 1000000009;
};

int TheExperiment::countPlacements(std::vector<std::string> intensity, int M, int L, int A, int B)
{
    std::string s;
    for (const auto &x : intensity) {
        s += x;
    }
    int n = s.length();
    std::vector<int> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + s[i] - '0';
    }
    // f[i][j][k] = number of ways to place j intervals into first i
    // cells, and each of them has length <= L, A <= sum <= B, and every
    // continuous component except last one has at least one interval
    // with length L, and k == whether last continuous component has one
    // as well
    std::vector<std::vector<std::pair<int, int>>> f(n + 1, std::vector<std::pair<int, int>>(M + 1));
    for (int i = 0; i <= n; i++) {
        f[i][0].first = 1;
    }
    for (int i = 0; i < n; i++) {
        // End current continuous component and add spaces
        for (int j = 0; j <= M; j++) {
            for (int k = 1; k <= n - i; k++) {
                f[i + k][j].first = (f[i + k][j].first + f[i][j].second) % MOD;
            }
        }
        // Add another interval to current continuous component
        for (int j = 0; j < M; j++) {
            for (int k = 1; k <= n - i && k <= L; k++) {
                if (sum[i + k] - sum[i] >= A && sum[i + k] - sum[i] <= B) {
                    f[i + k][j + 1].second = (f[i + k][j + 1].second + f[i][j].second) % MOD;
                    if (k == L) {
                        f[i + k][j + 1].second = (f[i + k][j + 1].second + f[i][j].first) % MOD;
                    } else {
                        f[i + k][j + 1].first = (f[i + k][j + 1].first + f[i][j].first) % MOD;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = (ans + f[i][M].second) % MOD;
    }
    return ans;
}
