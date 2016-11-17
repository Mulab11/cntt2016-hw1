#include <algorithm>
#include <vector>

class BinPacking {
  public:
    int minBins(std::vector<int> item);

  private:
    int minBins2(const std::vector<int> &itemsorted);
};

int BinPacking::minBins(std::vector<int> item)
{
    std::sort(item.begin(), item.end());
    // The only way to put 3 items in one bin is to have 3 items with
    // weight 100
    // Enumerate the number of bins with 3 items
    int ans = minBins2(item);
    int cntbin3 = 0;
    while (item.size() >= 3 && item[2] == 100) {
        cntbin3 += 1;
        item.erase(item.begin(), item.begin() + 3);
        ans = std::min(ans, cntbin3 + minBins2(item));
    }
    return ans;
}

int BinPacking::minBins2(const std::vector<int> &itemsorted)
{
    if (itemsorted.empty()) {
        return 0;
    }
    int ans = itemsorted.size();
    // Match items greedily
    auto r = itemsorted.end() - 1;
    for (auto l = itemsorted.begin(); l != r; l++) {
        while (l != r && *l + *r > 300) {
            r--;
        }
        if (l == r) {
            break;
        }
        r--;
        ans--;
        if (l == r) {
            break;
        }
    }
    return ans;
}
