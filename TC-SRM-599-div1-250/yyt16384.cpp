#include <algorithm>
#include <utility>
#include <vector>

class BigFatInteger {
  public:
    int minOperations(int A, int B);

  private:
    std::vector<std::pair<int, int>> factor(int x);
};

int BigFatInteger::minOperations(int A, int B)
{
    std::vector<std::pair<int, int>> fs = factor(A);
    int ans1 = fs.size();  // Each prime factor requires an operation 1
    int maxcnt = 0;
    for (auto x : fs) {
        maxcnt = std::max(maxcnt, x.second);
    }
    int ans2 = 0;
    for (int cur = 1; cur < maxcnt * B; cur *= 2) {
        ans2++;  // Each operation 2 doubles the maximum count of each prime factor
    }
    return ans1 + ans2;
}

std::vector<std::pair<int, int>> BigFatInteger::factor(int x)
{
    std::vector<std::pair<int, int>> fs;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) {
                x /= i;
                cnt++;
            }
            fs.push_back(std::make_pair(i, cnt));
        }
    }
    if (x > 1) {
        fs.push_back(std::make_pair(x, 1));
    }
    return fs;
}
