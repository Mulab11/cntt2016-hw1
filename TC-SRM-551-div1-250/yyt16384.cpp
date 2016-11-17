#include <algorithm>
#include <string>
#include <vector>

class ColorfulChocolates {
  public:
    int maximumSpread(std::string chocolates, int maxSwaps);
};

int ColorfulChocolates::maximumSpread(std::string chocolates, int maxSwaps)
{
    int n = chocolates.length();
    int ans = 1;
    // Enumerate the first element in the answer
    for (int i = 0; i < n; i++) {
        std::vector<int> c = {i};
        int suml = 0;
        int sumr = i;
        // Enumerate the last element in the answer
        for (int j = i + 1; j < n; j++) {
            if (chocolates[j] == chocolates[i]) {
                c.push_back(j - c.size());
                sumr += c.back();
                if (c.size() % 2 == 0) {
                    suml += c[c.size() / 2 - 1];
                    sumr -= c[c.size() / 2 - 1];
                }
                // Move selected elements together
                int cost = c.size() / 2 * c[c.size() / 2] - suml + sumr - (c.size() - c.size() / 2) * c[c.size() / 2];
                if (cost <= maxSwaps) {
                    ans = std::max<int>(ans, c.size());
                }
            }
        }
    }
    return ans;
}
