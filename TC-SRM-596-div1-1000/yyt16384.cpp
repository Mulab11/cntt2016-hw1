#include <algorithm>
#include <utility>
#include <vector>

class SparseFactorial {
  public:
    long long getCount(long long lo, long long hi, long long divisor);

  private:
    std::vector<int> prepare(int d);
    std::vector<std::pair<int, int>> factor(int x);
};

long long SparseFactorial::getCount(long long lo, long long hi, long long divisor)
{
    // If F(n) is divisible by divisor, then F(n + divisor) is also
    // divisible by divisor
    // Find the minimum n for each remainder
    std::vector<int> minxs = prepare(divisor);
    long long ans = 0;
    for (int i = 0; i < divisor; i++) {
        if (minxs[i] == -1) {
            continue;
        }
        long long x = (long long)minxs[i] * minxs[i] + 1;
        x = (x + divisor - i - 1) / divisor * divisor + i;
        long long cntr = x <= hi ? (hi - x) / divisor + 1 : 0;
        long long cntl = x <= lo - 1 ? (lo - 1 - x) / divisor + 1 : 0;
        ans += cntr - cntl;
    }
    return ans;
}

std::vector<int> SparseFactorial::prepare(int d)
{
    std::vector<std::pair<int, int>> fs = factor(d);
    std::vector<std::vector<int>> sqrtlists;
    for (auto x : fs) {
        int p = x.first;
        std::vector<int> g(p, -1);
        for (int i = 0; 2 * i <= p; i++) {
            int u = (long long)i * i % p;
            g[u] = i;
        }
        sqrtlists.push_back(std::move(g));
    }
    std::vector<int> minxs(d);
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < (int)fs.size(); j++) {
            int p = fs[j].first;
            if (sqrtlists[j][i % p] == -1) {
                minxs[i] = -1;
                break;
            }
            int cnt = 0;
            int u = sqrtlists[j][i % p];
            int now = u;
            // Try numbers that can provide the prime factor p
            while (true) {
                int x = ((long long)now * now - i + d) % d + d;
                while (x % p == 0) {
                    x /= p;
                    cnt++;
                }
                if (cnt >= fs[j].second) {
                    break;
                }
                if (now % p == u && !(p == 2 && u == 1)) {
                    now += p - 2 * u;
                } else {
                    now += 2 * u;
                }
            }
            minxs[i] = std::max(minxs[i], now);
        }
    }
    return minxs;
}

std::vector<std::pair<int, int>> SparseFactorial::factor(int x)
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
