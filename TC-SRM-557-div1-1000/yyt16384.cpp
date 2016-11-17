#include <utility>
#include <vector>

class XorAndSum {
  public:
    long long maxSum(std::vector<long long> number);

  private:
    static const int MAXBITS = 50;

    std::vector<long long> gaussianElimination(std::vector<long long> f);
};

long long XorAndSum::maxSum(std::vector<long long> number)
{
    std::vector<long long> f = gaussianElimination(number);
    std::vector<long long> s(number.size());
    for (int i = 0; i < (int)number.size() && f[i] != 0; i++) {
        for (int j = 0; j < (int)number.size(); j++) {
            // The first bit is added n times, while any later bit that
            // is in the basis
            if (j != i - 1) {
                s[j] ^= f[i];
            }
        }
    }
    long long ans = 0;
    for (auto x : s) {
        ans += x;
    }
    return ans;
}

std::vector<long long> XorAndSum::gaussianElimination(std::vector<long long> f)
{
    int cur = 0;
    for (int i = MAXBITS - 1; i >= 0; i--) {
        int r = -1;
        for (int j = cur; j < (int)f.size(); j++) {
            if ((f[j] >> i) & 1) {
                r = j;
                break;
            }
        }
        if (r == -1) {
            continue;
        }
        std::swap(f[cur], f[r]);
        for (int j = 0; j < (int)f.size(); j++) {
            if (j != cur && ((f[j] >> i) & 1)) {
                f[j] ^= f[cur];
            }
        }
        cur++;
    }
    return f;
}
