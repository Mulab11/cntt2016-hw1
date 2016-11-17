#include <array>
#include <map>
#include <string>
#include <utility>
#include <vector>

static int powermod(int x, int y, int m)
{
    int s = 1;
    while (y) {
        if (y & 1) {
            s = (long long)s * x % m;
        }
        x = (long long)x * x % m;
        y >>= 1;
    }
    return s;
}

class ConversionMachine {
  public:
    int countAll(std::string word1, std::string word2, std::vector<int> costs, int maxCost);

  private:
    static const int MOD = 1000000007;

    std::pair<int, int> add(std::pair<int, int> x, std::pair<int, int> y);
    std::pair<int, int> multiply(std::pair<int, int> x, std::pair<int, int> y);
    std::pair<int, int> getSum(std::pair<int, int> x, int n);
    std::pair<std::pair<int, int>, std::pair<int, int>> getSumAndPower(std::pair<int, int> x, int n);
};

int ConversionMachine::countAll(std::string word1, std::string word2, std::vector<int> costs, int maxCost)
{
    long long mincost = 0;
    std::vector<int> ps(word1.length());
    int tot = 0;
    for (int i = 0; i < (int)word1.length(); i++) {
        int u = word1[i] - 'a';
        int v = word2[i] - 'a';
        ps[i] = (v - u + 3) % 3;
        tot += ps[i];
        int s = 0;
        while (u != v) {
            s += costs[u];
            u = (u + 1) % 3;
        }
        mincost += s;
    }
    if (mincost > maxCost) {
        return 0;
    }
    int maxcnt = (maxCost - mincost) / ((long long)costs[0] + costs[1] + costs[2]) * 3 + tot;
    std::array<std::pair<int, int>, 3> ws = {{{1, 0}, {0, 1}, {MOD - 1, MOD - 1}}};
    std::map<std::pair<int, int>, std::pair<int, int>> vals = {{{0, 0}, {1, 0}}};
    for (auto w : ps) {
        std::map<std::pair<int, int>, std::pair<int, int>> valsnow;
        // Multiply the exponential generating function of x
        for (int i = 0; i < 3; i++) {
            std::pair<int, int> u = ws[(3 - w) * i % 3];
            std::pair<int, int> v = ws[i];
            for (auto p : vals) {
                std::pair<int, int> x = multiply(u, p.second);
                std::pair<int, int> y = add(v, p.first);
                valsnow[y] = add(valsnow[y], x);
            }
        }
        vals = std::move(valsnow);
    }
    int ans = 0;
    for (auto x : vals) {
        std::pair<int, int> u = x.first;
        std::pair<int, int> v = x.second;
        // Add the term v * e^u to answer
        std::pair<int, int> t = getSum(u, maxcnt + 1);
        std::pair<int, int> s = multiply(t, v);
        ans = (ans + s.first) % MOD;
    }
    int pw3 = 1;
    for (int i = 0; i < (int)word1.size(); i++) {
        pw3 = (long long)pw3 * 3 % MOD;
    }
    return ans * (long long)powermod(pw3, MOD - 2, MOD) % MOD;
}

std::pair<int, int> ConversionMachine::add(std::pair<int, int> x, std::pair<int, int> y)
{
    return std::make_pair((x.first + y.first) % MOD, (x.second + y.second) % MOD);
}

std::pair<int, int> ConversionMachine::multiply(std::pair<int, int> x, std::pair<int, int> y)
{
    return std::make_pair((((long long)x.first * y.first - (long long)x.second * y.second) % MOD + MOD) % MOD, (((long long)x.first * y.second + (long long)x.second * y.first - (long long)x.second * y.second) % MOD + MOD) % MOD);
}

std::pair<int, int> ConversionMachine::getSum(std::pair<int, int> x, int n)
{
    // Get sum(x**i for i in range(n))
    return getSumAndPower(x, n).first;
}

std::pair<std::pair<int, int>, std::pair<int, int>> ConversionMachine::getSumAndPower(std::pair<int, int> x, int n)
{
    if (n == 0) {
        return std::make_pair(std::make_pair(0, 0), std::make_pair(1, 0));
    }
    auto s = getSumAndPower(x, n / 2);
    std::pair<int, int> u = add(s.first, multiply(s.first, s.second));
    std::pair<int, int> v = multiply(s.second, s.second);
    if (n % 2) {
        u = add(std::make_pair(1, 0), multiply(u, x));
        v = multiply(v, x);
    }
    return std::make_pair(u, v);
}
