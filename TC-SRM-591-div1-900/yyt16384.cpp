#include <string>
#include <utility>
#include <vector>

class StringPath {
  public:
    int countBoards(int n, int m, std::string A, std::string B);

  private:
    static const int MOD = 1000000009;
    static const int SZ = 26;
};

int StringPath::countBoards(int n, int m, std::string A, std::string B)
{
    // f[i][j] = number of partial boards where the lowermost cells of
    // columns in set i are valid endpoints of string A, and the
    // lowermost cells of columns in set j are valid endpoints of string
    // B
    std::vector<std::vector<int>> f(1 << m, std::vector<int>(1 << m));
    f[1][1] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::vector<std::vector<int>> g(1 << m, std::vector<int>(1 << m));
            for (int p = 0; p < (1 << m); p++) {
                for (int q = 0; q < (1 << m); q++) {
                    bool oka = ((p >> j) & 1) || (j ? (p >> (j - 1)) & 1 : false);
                    bool okb = ((q >> j) & 1) || (j ? (q >> (j - 1)) & 1 : false);
                    bool ok11 = false;
                    bool ok10 = false;
                    bool ok01 = false;
                    if (oka && okb) {
                        if (A[i + j] == B[i + j]) {
                            ok11 = true;
                        } else {
                            ok10 = true;
                            ok01 = true;
                        }
                    } else if (oka) {
                        ok10 = true;
                    } else if (okb) {
                        ok01 = true;
                    }
                    int u0 = p & ~(1 << j);
                    int u1 = p | (1 << j);
                    int v0 = q & ~(1 << j);
                    int v1 = q | (1 << j);
                    if (ok11) {
                        g[u1][v1] = (g[u1][v1] + f[p][q]) % MOD;
                    }
                    if (ok10) {
                        g[u1][v0] = (g[u1][v0] + f[p][q]) % MOD;
                    }
                    if (ok01) {
                        g[u0][v1] = (g[u0][v1] + f[p][q]) % MOD;
                    }
                    g[u0][v0] = (g[u0][v0] + (long long)f[p][q] * (SZ - ok11 - ok10 - ok01)) % MOD;
                }
            }
            f = std::move(g);
        }
    }
    int ans = 0;
    for (int i = 1 << (m - 1); i < (1 << m); i++) {
        for (int j = 1 << (m - 1); j < (1 << m); j++) {
            ans = (ans + f[i][j]) % MOD;
        }
    }
    return ans;
}
