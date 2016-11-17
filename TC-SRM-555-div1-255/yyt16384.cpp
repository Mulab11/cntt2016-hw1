#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

static const int INF = 0x3f3f3f3f;

class CuttingBitString {
  public:
    int getmin(std::string S);
};

int CuttingBitString::getmin(std::string S)
{
    int n = S.length();
    std::unordered_set<long long> c;
    for (long long i = 1; i < (1LL << n); i *= 5) {
        c.insert(i);
    }
    // f[i] = minimum parts after splitting the first i bits
    std::vector<int> f(n + 1, INF);
    f[0] = 0;
    for (int i = 0; i < n; i++) {
        if (S[i] == '1') {
            long long s = 0;
            for (int j = i + 1; j <= n; j++) {
                s = s * 2 + S[j - 1] - '0';
                if (c.find(s) != c.end()) {
                    f[j] = std::min(f[j], f[i] + 1);
                }
            }
        }
    }
    return f[n] == INF ? -1 : f[n];
}
