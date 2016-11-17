#include <string>
#include <vector>

class TheSwapsDivOne {
  public:
    double find(std::vector<std::string> sequence, int k);
};

double TheSwapsDivOne::find(std::vector<std::string> sequence, int k)
{
    std::string s;
    for (const auto &x : sequence) {
        s += x;
    }
    int n = s.length();
    // Probability of an element staying in the same position after k
    // swaps
    double ps = 1;
    for (int i = 0; i < k; i++) {
        ps = ps * (n - 2) / n + (1 - ps) * 2 / n / (n - 1);
    }
    int sum = 0;
    for (auto x : s) {
        sum += x - '0';
    }
    double ans = 0;
    for (int i = 0; i < n; i++) {
        // Expected value in this position after k swaps
        double val = ps * (s[i] - '0') + (1 - ps) * (sum - s[i] + '0') / (n - 1);
        double pcover = (double)(i + 1) * (n - i) * 2 / n / (n + 1);
        ans += val * pcover;
    }
    return ans;
}
