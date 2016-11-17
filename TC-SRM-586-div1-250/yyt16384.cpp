#include <algorithm>
#include <utility>
#include <vector>

class PiecewiseLinearFunction {
  public:
    int maximumSolutions(std::vector<int> Y);
};

int PiecewiseLinearFunction::maximumSolutions(std::vector<int> Y)
{
    std::vector<std::pair<int, int>> c;
    // Multiply coordinates by 2 to avoid fractions
    for (int i = 0; i < (int)Y.size() - 1; i++) {
        if (Y[i] < Y[i + 1]) {
            c.push_back(std::make_pair(Y[i] * 2, 1));
            c.push_back(std::make_pair(Y[i + 1] * 2 + (i == (int)Y.size() - 2), -1));
        } else if (Y[i] > Y[i + 1]) {
            c.push_back(std::make_pair(Y[i + 1] * 2 + (i != (int)Y.size() - 2), 1));
            c.push_back(std::make_pair(Y[i] * 2 + 1, -1));
        } else {
            return -1;
        }
    }
    std::sort(c.begin(), c.end());
    int ans = 0;
    int s = 0;
    for (int i = 0; i < (int)c.size(); i++) {
        s += c[i].second;
        if (i == (int)c.size() - 1 || c[i].first != c[i + 1].first) {
            ans = std::max(ans, s);
        }
    }
    return ans;
}
