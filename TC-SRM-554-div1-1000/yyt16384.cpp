#include <algorithm>
#include <array>
#include <vector>

class TheBrickTowerHardDivOne {
  public:
    int find(int C, int K, long long H);

  private:
    static const int MOD = 1234567891;

    std::vector<std::array<int, 4>> ss;

    void initStates();
    int getStateID(const std::array<int, 4> &a);
    bool isSameState(const std::array<int, 4> &a, const std::array<int, 4> &b);
    std::vector<std::vector<int>> matrixMultiplication(const std::vector<std::vector<int>> &x, const std::vector<std::vector<int>> &y);
};

int TheBrickTowerHardDivOne::find(int C, int K, long long H)
{
    initStates();
    int n = ss.size() * (K + 1) + 1;
    std::array<std::vector<std::vector<int>>, 4> g;
    for (int i = 0; i < 4; i++) {
        g[i].resize(n, std::vector<int>(n));
        g[i][n - 1][n - 1] = 1;
    }
    for (int i = 0; i < (int)ss.size(); i++) {
        std::array<int, 4> s = ss[i];
        int maxval = *std::max_element(s.begin(), s.end());
        if (maxval >= C) {
            continue;
        }
        for (int j = 0; j <= maxval + 1; j++) {
            int cnt = j <= maxval ? 1 : C - maxval - 1;
            for (int k = 0; k < 4; k++) {
                // Add a brick with color j at position k from current
                // state
                std::array<int, 4> t = s;
                t[k] = j;
                int id = getStateID(t);
                int samepairs = (j == s[k]) + (k % 2 && j == s[k - 1]) + (k / 2 && j == s[k - 2]);
                for (int p = 0; p <= K - samepairs; p++) {
                    int x = i * (K + 1) + p;
                    int y = id * (K + 1) + p + samepairs;
                    g[k][y][x] += cnt;
                }
            }
        }
    }
    std::vector<std::vector<int>> gs(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        gs[i][i] = 1;
    }
    for (int i = 0; i < n - 1; i++) {
        gs[n - 1][i] = 1;
    }
    for (int i = 0; i < 4; i++) {
        gs = matrixMultiplication(g[i], gs);
    }
    std::vector<std::vector<int>> fs(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        fs[i][i] = 1;
    }
    long long t = H;
    while (t) {
        if (t & 1) {
            fs = matrixMultiplication(fs, gs);
        }
        gs = matrixMultiplication(gs, gs);
        t >>= 1;
    }
    int ans = 0;
    for (int i = 0; i < (int)ss.size(); i++) {
        int sp = (ss[i][0] == ss[i][1]) + (ss[i][2] == ss[i][3]) + (ss[i][0] == ss[i][2]) + (ss[i][1] == ss[i][3]);
        if (sp > K) {
            continue;
        }
        int maxval = *std::max_element(ss[i].begin(), ss[i].end());
        int s = fs[n - 1][i * (K + 1) + sp];
        for (int j = 0; j <= maxval; j++) {
            s = (long long)s * (C - j) % MOD;
        }
        ans = ((long long)ans + s) % MOD;
    }
    return ans;
}

void TheBrickTowerHardDivOne::initStates()
{
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= i + 1; j++) {
            for (int k = 0; k <= std::max(i, j) + 1; k++) {
                ss.push_back({0, i, j, k});
            }
        }
    }
}

int TheBrickTowerHardDivOne::getStateID(const std::array<int, 4> &a)
{
    for (int i = 0; i < (int)ss.size(); i++) {
        if (isSameState(a, ss[i])) {
            return i;
        }
    }
    return -1;
}

bool TheBrickTowerHardDivOne::isSameState(const std::array<int, 4> &a, const std::array<int, 4> &b)
{
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if ((a[i] == a[j]) != (b[i] == b[j])) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::vector<int>> TheBrickTowerHardDivOne::matrixMultiplication(const std::vector<std::vector<int>> &x, const std::vector<std::vector<int>> &y)
{
    std::vector<std::vector<int>> z(x.size(), std::vector<int>(y[0].size()));
    for (int i = 0; i < (int)x.size(); i++) {
        for (int j = 0; j < (int)y[0].size(); j++) {
            for (int k = 0; k < (int)x[0].size(); k++) {
                z[i][j] = (z[i][j] + (long long)x[i][k] * y[k][j]) % MOD;
            }
        }
    }
    return z;
}
