#include <algorithm>
#include <cstdlib>
#include <map>
#include <string>
#include <utility>
#include <vector>

class Mountains {
  public:
    int countPlacements(std::vector<int> heights, std::vector<std::string> visibility);

  private:
    static const int MOD = 1000000009;

    std::map<std::pair<int, std::vector<int>>, int> fstore;

    int recurse(int x, const std::vector<int> &h, const std::vector<int> &c, const std::vector<std::string> &visibility);
};

int Mountains::countPlacements(std::vector<int> heights, std::vector<std::string> visibility)
{
    int n = heights.size();
    int w = visibility[0].size();
    fstore.clear();
    return recurse(n - 1, std::vector<int>(w), heights, visibility);
}

int Mountains::recurse(int x, const std::vector<int> &h, const std::vector<int> &c, const std::vector<std::string> &visibility)
{
    auto it = fstore.find(std::make_pair(x, h));
    if (it != fstore.end()) {
        return it->second;
    }
    if (x == -1) {
        return 1;
    }
    int ans = 0;
    // Enumerate current mountain position
    for (int i = 0; i < (int)h.size(); i++) {
        bool ok = true;
        for (int j = 0; j < (int)h.size(); j++) {
            if ((c[x] - std::abs(j - i) > h[j]) != (visibility[x][j] == 'X')) {
                ok = false;
                break;
            }
        }
        if (ok) {
            std::vector<int> nh(h.size());
            for (int j = 0; j < (int)h.size(); j++) {
                nh[j] = std::max(h[j], c[x] - std::abs(j - i));
            }
            ans = (ans + recurse(x - 1, nh, c, visibility)) % MOD;
        }
    }
    fstore[std::make_pair(x, h)] = ans;
    return ans;
}
