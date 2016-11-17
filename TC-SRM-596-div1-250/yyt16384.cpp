#include <algorithm>
#include <vector>

class IncrementAndDoubling {
  public:
    int getMin(std::vector<int> desiredArray);
};

int IncrementAndDoubling::getMin(std::vector<int> desiredArray)
{
    int maxbits = 1;
    int ans = 0;
    for (auto x : desiredArray) {
        int bits = 0;
        while (x) {
            // Use an increment operation to set this bit to 1
            ans += x % 2;
            x /= 2;
            bits++;
        }
        maxbits = std::max(maxbits, bits);
    }
    // Number of doubling operations needed
    ans += maxbits - 1;
    return ans;
}
