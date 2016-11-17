#include <algorithm>
#include <vector>

class XorBoard {
  public:
    int count(int H, int W, int Rcount, int Ccount, int S);

  private:
    static const int MOD = 555555555;
};

int XorBoard::count(int H, int W, int Rcount, int Ccount, int S)
{
    int n = std::max({H, W, Rcount / 2 + H - 1, Ccount / 2 + W - 1});
    std::vector<std::vector<int>> cc(n + 1, std::vector<int>(n + 1));
    cc[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        cc[i][0] = 1;
        cc[i][i] = 1;
        for (int j = 1; j < i; j++) {
            cc[i][j] = (cc[i - 1][j - 1] + cc[i - 1][j]) % MOD;
        }
    }
    int ans = 0;
    // Enumerate the number of rows flipped for odd times
    for (int x = Rcount % 2; x <= H && x <= Rcount; x += 2) {
        // Enumerate the number of columns flipped for odd times
        for (int y = Ccount % 2; y <= W && y <= Ccount; y += 2) {
            if (x * W + y * H - 2 * x * y == S) {
                int remx = (Rcount - x) / 2;
                int remy = (Ccount - y) / 2;
                int s1 = (long long)cc[H][x] * cc[remx + H - 1][H - 1] % MOD;
                int s2 = (long long)cc[W][y] * cc[remy + W - 1][W - 1] % MOD;
                ans = (ans + (long long)s1 * s2) % MOD;
            }
        }
    }
    return ans;
}
