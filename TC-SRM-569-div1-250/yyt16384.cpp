#include <algorithm>
#include <string>
#include <vector>

class TheDevice {
  public:
    int minimumAdditional(std::vector<std::string> plates);
};

int TheDevice::minimumAdditional(std::vector<std::string> plates)
{
    int ans = 0;
    for (int i = 0; i < (int)plates[0].length(); i++) {
        int cnt0 = 0;
        int cnt1 = 0;
        for (const auto &x : plates) {
            if (x[i] == '0') {
                cnt0++;
            } else {
                cnt1++;
            }
        }
        // Need to test (0, 1) and (1, 1), so one '0' and two '1's
        // required
        int s = std::max(1 - cnt0, 0) + std::max(2 - cnt1, 0);
        ans = std::max(ans, s);
    }
    return ans;
}
