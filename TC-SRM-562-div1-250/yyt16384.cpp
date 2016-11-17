#include <algorithm>
#include <string>
#include <vector>

class PastingPaintingDivOne {
  public:
    std::vector<long long> countColors(std::vector<std::string> clipboard, int T);
};

std::vector<long long> PastingPaintingDivOne::countColors(std::vector<std::string> clipboard, int T)
{
    int n = clipboard.size();
    int m = clipboard[0].length();
    int p = std::min(n, m);
    long long cntr = 0;
    long long cntg = 0;
    long long cntb = 0;
    std::vector<std::vector<char>> visible(n, std::vector<char>(m, true));
    for (int i = 0; i < p && i < T; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (visible[j][k]) {
                    if (clipboard[j][k] == 'R') {
                        cntr++;
                    } else if (clipboard[j][k] == 'G') {
                        cntg++;
                    } else if (clipboard[j][k] == 'B') {
                        cntb++;
                    }
                }
            }
        }
        for (int j = 0; j < n - i - 1; j++) {
            for (int k = 0; k < m - i - 1; k++) {
                if (clipboard[j][k] != '.') {
                    visible[j + i + 1][k + i + 1] = false;
                }
            }
        }
    }
    // Remaining pictures are the same
    int rem = T - std::min(p, T);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (visible[i][j]) {
                if (clipboard[i][j] == 'R') {
                    cntr += rem;
                } else if (clipboard[i][j] == 'G') {
                    cntg += rem;
                } else if (clipboard[i][j] == 'B') {
                    cntb += rem;
                }
            }
        }
    }
    return {cntr, cntg, cntb};
}
