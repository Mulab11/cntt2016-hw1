#include <algorithm>
#include <functional>
#include <string>
#include <utility>
#include <vector>

static const int INF = 0x3f3f3f3f;

class ICPCBalloons {
  public:
    int minRepaintings(std::vector<int> balloonCount, std::string balloonSize, std::vector<int> maxAccepted);
};

int ICPCBalloons::minRepaintings(std::vector<int> balloonCount, std::string balloonSize, std::vector<int> maxAccepted)
{
    int m = maxAccepted.size();
    std::vector<int> c1;
    std::vector<int> c2;
    for (int i = 0; i < (int)balloonCount.size(); i++) {
        if (balloonSize[i] == 'M') {
            c1.push_back(balloonCount[i]);
        } else {
            c2.push_back(balloonCount[i]);
        }
    }
    std::sort(c1.begin(), c1.end(), std::greater<int>());
    std::sort(c2.begin(), c2.end(), std::greater<int>());
    std::vector<int> a = maxAccepted;
    std::sort(a.begin(), a.end(), std::greater<int>());
    int n1 = c1.size();
    int n2 = c2.size();
    int maxsum = 0;
    for (auto x : a) {
        maxsum += x;
    }
    // f[i][j] = minimum cost to choose i problems to use j medium
    // balloons
    std::vector<std::vector<int>> f(m + 1, std::vector<int>(maxsum + 1, INF));
    int cursum = 0;
    f[0][0] = 0;
    for (int i = 0; i < m; i++) {
        std::vector<std::vector<int>> g(m + 1, std::vector<int>(maxsum + 1, INF));
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k <= cursum; k++) {
                int w0 = a[i] - std::min(i - j >= n2 ? 0 : c2[i - j], a[i]);
                int w1 = a[i] - std::min(j >= n1 ? 0 : c1[j], a[i]);
                g[j][k] = std::min(g[j][k], f[j][k] + w0);
                g[j + 1][k + a[i]] = std::min(g[j + 1][k + a[i]], f[j][k] + w1);
            }
        }
        f = std::move(g);
        cursum += a[i];
    }
    int sumc1 = 0;
    for (auto x : c1) {
        sumc1 += x;
    }
    int sumc2 = 0;
    for (auto x : c2) {
        sumc2 += x;
    }
    int ans = INF;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= cursum; j++) {
            if (j <= sumc1 && cursum - j <= sumc2) {
                ans = std::min(ans, f[i][j]);
            }
        }
    }
    return ans == INF ? -1 : ans;
}
