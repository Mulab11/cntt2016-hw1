#include <algorithm>
#include <vector>

static const int INF = 0x3f3f3f3f;

class DrawingPointsDivOne {
  public:
    int maxSteps(std::vector<int> x, std::vector<int> y);
};

int DrawingPointsDivOne::maxSteps(std::vector<int> x, std::vector<int> y)
{
    int n = x.size();
    int minx = INF;
    int maxx = -INF;
    int miny = INF;
    int maxy = -INF;
    for (auto p : x) {
        minx = std::min(minx, p);
        maxx = std::max(maxx, p);
    }
    for (auto p : y) {
        miny = std::min(miny, p);
        maxy = std::max(maxy, p);
    }
    int lim = std::max(maxx - minx, maxy - miny);
    int cur = 0;
    std::vector<std::vector<char>> haspoint(maxx - minx + 1, std::vector<char>(maxy - miny + 1));
    for (int i = 0; i < n; i++) {
        haspoint[x[i] - minx][y[i] - miny] = true;
    }
    std::vector<std::vector<char>> cov(maxx - minx + lim, std::vector<char>(maxy - miny + lim));
    // Any finite answer will be less than lim
    while (cur < lim) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= cur; j++) {
                cov[x[i] - minx + cur][y[i] - miny + j] = true;
                cov[x[i] - minx + j][y[i] - miny + cur] = true;
            }
        }
        std::vector<std::vector<int>> sum(maxx - minx + cur + 2, std::vector<int>(maxy - miny + cur + 2));
        for (int i = 0; i <= maxx - minx + cur; i++) {
            for (int j = 0; j <= maxy - miny + cur; j++) {
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + cov[i][j];
            }
        }
        bool ok = true;
        for (int i = 0; i <= maxx - minx; i++) {
            for (int j = 0; j <= maxy - miny; j++) {
                if (!haspoint[i][j] && sum[i + cur + 1][j + cur + 1] - sum[i][j + cur + 1] - sum[i + cur + 1][j] + sum[i][j] == (cur + 1) * (cur + 1)) {
                    // This point should be drawn according to existing
                    // points in the beginning, but it is not drawn, so
                    // increasing answer is not OK
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                break;
            }
        }
        if (!ok) {
            break;
        }
        cur++;
    }
    return cur == lim ? -1 : cur - 1;
}
