#include <string>
#include <vector>

class MapGuessing {
  public:
    long long countPatterns(std::string goal, std::vector<std::string> code);

  private:
    long long recurse(int x, long long s, const std::vector<long long> c);
};

long long MapGuessing::countPatterns(std::string goal, std::vector<std::string> code)
{
    std::string s;
    for (const auto &x : code) {
        s += x;
    }
    int n = goal.length();
    std::vector<long long> c(n);
    long long g = 0;
    for (int i = 0; i < n; i++) {
        if (goal[i] == '1') {
            g |= 1LL << i;
        }
    }
    // Enumerate the starting position
    bool anyok = false;
    for (int i = 0; i < n; i++) {
        long long p0 = 0;
        long long p1 = 0;
        int cur = i;
        long long pf = 0;
        bool ok = true;
        for (auto x : s) {
            if (x == '<') {
                cur--;
            } else if (x == '>') {
                cur++;
            } else if (x == '0') {
                p0 |= 1LL << cur;
                p1 &= ~(1LL << cur);
            } else {
                p0 &= ~(1LL << cur);
                p1 |= 1LL << cur;
            }
            if (cur < 0 || cur >= n) {
                pf = 0;
                ok = false;
                break;
            }
            if ((p0 & ~g) == p0 && (p1 & g) == p1) {
                pf = p0 | p1;
            }
        }
        c[i] = pf;
        if (ok) {
            anyok = true;
        }
    }
    if (!anyok) {
        return 0;
    } else {
        return (1LL << n) - recurse(0, (1LL << n) - 1, c);
    }
}

long long MapGuessing::recurse(int x, long long s, const std::vector<long long> c)
{
    if (x == (int)c.size()) {
        int cnt = 0;
        for (long long u = s; u > 0; u &= u - 1) {
            cnt++;
        }
        return 1LL << cnt;
    }
    if (s == 0) {
        return 0;
    }
    return recurse(x + 1, s, c) - recurse(x + 1, s & c[x], c);
}
