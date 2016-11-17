#include <algorithm>
#include <functional>
#include <vector>

class TomekPhone {
  public:
    int minKeystrokes(std::vector<int> frequencies, std::vector<int> keySizes);
};

int TomekPhone::minKeystrokes(std::vector<int> frequencies, std::vector<int> keySizes)
{
    std::vector<int> a = frequencies;
    std::sort(a.begin(), a.end(), std::greater<int>());
    std::vector<int> cur(keySizes.size());
    int ans = 0;
    for (auto x : a) {
        int r = -1;
        for (int i = 0; i < (int)keySizes.size(); i++) {
            if (cur[i] < keySizes[i] && (r == -1 || cur[i] < cur[r])) {
                r = i;
            }
        }
        if (r == -1) {
            // Not enough space
            return -1;
        }
        cur[r]++;
        ans += cur[r] * x;
    }
    return ans;
}
