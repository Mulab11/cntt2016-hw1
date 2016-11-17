#include <algorithm>
#include <vector>

class KingdomAndTrees {
  public:
    int minLevel(std::vector<int> heights);
};

int KingdomAndTrees::minLevel(std::vector<int> heights)
{
    int ans = 0;
    for (int i = 0; i < (int)heights.size(); i++) {
        for (int j = i + 1; j < (int)heights.size(); j++) {
            // The height of tree i must be lower than the height of
            // tree j
            int diff = j - i - heights[j] + heights[i];
            ans = std::max(ans, std::max((diff + 1) / 2, diff - heights[i] + i + 1));
        }
    }
    return ans;
}
