#include <vector>

class TheBrickTowerMediumDivOne {
  public:
    std::vector<int> find(std::vector<int> heights);
};

std::vector<int> TheBrickTowerMediumDivOne::find(std::vector<int> heights)
{
    int n = heights.size();
    std::vector<char> vis(n);
    std::vector<int> ans = {0};
    vis[0] = true;
    // The first part should have decreasing heights
    while (true) {
        int r = -1;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && heights[i] <= heights[ans.back()]) {
                r = i;
                break;
            }
        }
        if (r == -1) {
            break;
        }
        ans.push_back(r);
        vis[r] = true;
    }
    // The second part contains the remaining towers and should have
    // increasing heights
    while (true) {
        int r = -1;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && (r == -1 || heights[i] < heights[r])) {
                r = i;
            }
        }
        if (r == -1) {
            break;
        }
        ans.push_back(r);
        vis[r] = true;
    }
    return ans;
}
