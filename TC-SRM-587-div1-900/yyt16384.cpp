#include <string>
#include <utility>
#include <vector>

class ThreeColorability {
  public:
    std::vector<std::string> lexSmallest(std::vector<std::string> cells);

  private:
    std::vector<std::pair<std::vector<char>, bool>> gaussianElimination(std::vector<std::pair<std::vector<char>, bool>> f);
};

std::vector<std::string> ThreeColorability::lexSmallest(std::vector<std::string> cells)
{
    int n = cells.size();
    int m = cells[0].length();
    std::vector<std::pair<std::vector<char>, bool>> f;
    // For every 2x2 square, there should be even number of 'Z's and
    // even number of 'N's, so the whole board is determined by the
    // first row and the first column
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (cells[i][j] != '?') {
                std::vector<char> g(n + m - 1);
                if (i == 0) {
                    g[n + m - j - 2] = true;
                } else if (j == 0) {
                    g[n - i - 1] = true;
                } else {
                    g[n + m - 2] = true;
                    g[n + m - j - 2] = true;
                    g[n - i - 1] = true;
                }
                f.push_back(std::make_pair(std::move(g), cells[i][j] == 'Z'));
            }
        }
    }
    std::vector<std::pair<std::vector<char>, bool>> g = gaussianElimination(f);
    std::vector<std::vector<char>> ans(n, std::vector<char>(m));
    for (const auto &x : g) {
        int r = -1;
        for (int j = 0; j < n + m - 1; j++) {
            if (x.first[j]) {
                r = j;
                break;
            }
        }
        if (r == -1) {
            if (x.second) {
                return {};
            }
            continue;
        }
        if (r < n - 1) {
            ans[n - r - 1][0] = x.second;
        } else {
            ans[0][n + m - r - 2] = x.second;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            ans[i][j] = ans[i - 1][j] ^ ans[i][j - 1] ^ ans[i - 1][j - 1];
        }
    }
    std::vector<std::string> ansstr(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ansstr[i] += ans[i][j] ? 'Z' : 'N';
        }
    }
    return ansstr;
}

std::vector<std::pair<std::vector<char>, bool>> ThreeColorability::gaussianElimination(std::vector<std::pair<std::vector<char>, bool>> f)
{
    if (f.empty()) {
        return {};
    }
    int m = f[0].first.size();
    int cur = 0;
    for (int i = 0; i < m; i++) {
        int r = -1;
        for (int j = cur; j < (int)f.size(); j++) {
            if (f[j].first[i]) {
                r = j;
                break;
            }
        }
        if (r == -1) {
            continue;
        }
        std::swap(f[cur], f[r]);
        for (int j = 0; j < (int)f.size(); j++) {
            if (j != cur && f[j].first[i]) {
                for (int k = i; k < m; k++) {
                    f[j].first[k] ^= f[cur].first[k];
                }
                f[j].second ^= f[cur].second;
            }
        }
        cur++;
    }
    return f;
}
