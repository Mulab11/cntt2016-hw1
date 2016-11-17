#include <algorithm>
#include <vector>

static const int INF = 0x3f3f3f3f;

class BallsSeparating {
  public:
    int minOperations(std::vector<int> red, std::vector<int> green, std::vector<int> blue);
};

int BallsSeparating::minOperations(std::vector<int> red, std::vector<int> green, std::vector<int> blue)
{
    int n = red.size();
    bool nored = true;
    bool nogreen = true;
    bool noblue = true;
    for (auto x : red) {
        if (x) {
            nored = false;
            break;
        }
    }
    for (auto x : green) {
        if (x) {
            nogreen = false;
            break;
        }
    }
    for (auto x : blue) {
        if (x) {
            noblue = false;
            break;
        }
    }
    int ans = INF;
    // For each color, there should be at least one box ending up with
    // this color if there is at least one ball with this color
    for (int i = nored ? -1 : 0; i < (nored ? 0 : n); i++) {
        for (int j = nogreen ? -2 : 0; j < (nogreen ? -1 : n); j++) {
            if (j != i) {
                for (int k = noblue ? -3 : 0; k < (noblue ? -2 : n); k++) {
                    if (k != i && k != j) {
                        int s = 0;
                        if (!nored) {
                            s += green[i] + blue[i];
                        }
                        if (!nogreen) {
                            s += red[j] + blue[j];
                        }
                        if (!noblue) {
                            s += red[k] + green[k];
                        }
                        for (int p = 0; p < n; p++) {
                            if (p != i && p != j && p != k) {
                                s += red[p] + green[p] + blue[p] - std::max({red[p], green[p], blue[p]});
                            }
                        }
                        ans = std::min(ans, s);
                    }
                }
            }
        }
    }
    return ans == INF ? -1 : ans;
}
