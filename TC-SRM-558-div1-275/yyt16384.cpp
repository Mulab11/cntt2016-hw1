#include <algorithm>
#include <string>
#include <vector>

static const int INF = 0x3f3f3f3f;

class Stamp {
  public:
    int getMinimumCost(std::string desiredColor, int stampCost, int pushCost);
};

int Stamp::getMinimumCost(std::string desiredColor, int stampCost, int pushCost)
{
    int n = desiredColor.size();
    int ans = INF;
    // Enumerate the length of the stamp
    for (int l = 1; l <= n; l++) {
        std::vector<int> f(n + 1, INF);
        f[0] = 0;
        for (int i = 0; i < n; i++) {
            char col = '*';
            for (int j = i; j < n; j++) {
                if (desiredColor[j] != '*') {
                    if (col != '*' && col != desiredColor[j]) {
                        break;
                    }
                    col = desiredColor[j];
                }
                if (j - i + 1 >= l) {
                    f[j + 1] = std::min(f[j + 1], f[i] + (j - i) / l + 1);
                }
            }
        }
        if (f[n] < INF) {
            ans = std::min(ans, f[n] * pushCost + l * stampCost);
        }
    }
    return ans;
}
