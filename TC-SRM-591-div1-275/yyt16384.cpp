#include <algorithm>
#include <vector>

class TheTree {
  public:
    int maximumDiameter(std::vector<int> cnt);
};

int TheTree::maximumDiameter(std::vector<int> cnt)
{
    int d = cnt.size();
    int ans = 0;
    // Enumerate the depth of LCA
    for (int i = 0; i < d; i++) {
        int r = i;
        while (r < d && cnt[r] > 1) {
            r++;
        }
        // The first vertex has depth r and the second vertex has depth
        // d
        ans = std::max(ans, r - i + d - i);
    }
    return ans;
}
