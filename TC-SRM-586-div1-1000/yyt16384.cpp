#include <algorithm>
#include <array>
#include <vector>

static const int INF = 0x3f3f3f3f;

class StringWeight {
  public:
    int getMinimum(std::vector<int> L);

  private:
    static const int SZ = 26;
};

int StringWeight::getMinimum(std::vector<int> L)
{
    // f[i][j] = minimum weight with i letters started but not ended and
    // j letters ended
    std::array<std::array<int, SZ + 1>, SZ + 1> f;
    for (auto &x : f) {
        x.fill(INF);
    }
    f[0][0] = 0;
    for (auto u : L) {
        std::array<std::array<int, SZ + 1>, SZ + 1> g;
        for (auto &x : g) {
            x.fill(INF);
        }
        int c = std::min(u, (int)SZ);
        for (int i = 0; i <= SZ; i++) {
            for (int j = 0; j <= SZ - i; j++) {
                if (SZ - j < c) {
                    // Not enough letters for current part
                    continue;
                }
                // Enumerate the number of ended letters in current part
                for (int k = 0; k <= i && k <= c; k++) {
                    // Enumerate the number of started letters in
                    // current part
                    for (int p = 0; p <= SZ - i - j && p <= std::max(c - i, 0); p++) {
                        // Number of letters that only appear in this
                        // part
                        int q = std::max(c - i - p, 0);
                        int startw = k * (k - 1) / 2;
                        int endw = p * (p + 1) / 2;
                        int keepw = (i - k) * u;
                        int selfw = i - k ? 0 : std::max(u - SZ, 0);
                        int w = startw + endw + keepw + selfw;
                        g[i - k + p][j + k + q] = std::min(g[i - k + p][j + k + q], f[i][j] + w);
                    }
                }
            }
        }
        f = g;
    }
    return *std::min_element(f[0].begin(), f[0].end());
}
