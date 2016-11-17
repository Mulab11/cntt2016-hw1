#include <utility>
#include <vector>

class XorCards {
  public:
    long long numberOfWays(std::vector<long long> number, long long limit);

  private:
    static const int MAXBITS = 50;

    std::vector<long long> gaussianElimination(std::vector<long long> f);
};

long long XorCards::numberOfWays(std::vector<long long> number, long long limit)
{
    std::vector<long long> f = gaussianElimination(number);
    long long s = 0;
    long long ans = 0;
    for (int i = 0; i < (int)f.size(); i++) {
        if ((s ^ f[i]) <= limit) {
            s ^= f[i];
            // If current row is not used, remaining rows can be chosen
            // arbitrarily
            ans += 1LL << (f.size() - i - 1);
        }
    }
    ans++;
    return ans;
}

std::vector<long long> XorCards::gaussianElimination(std::vector<long long> f)
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
