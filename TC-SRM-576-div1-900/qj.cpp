#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class CharacterBoard {
  static const int MOD = 1000000009;
  int power(int base, int exp) {
    int res = 1;
    for (; exp; exp >>= 1) {
      if (exp & 1) res = (i64)res * base % MOD;
      base = (i64)base * base % MOD;
    }
    return res;
  }
  int n;
  std::vector<i64> p, d;
  std::string q;
  void sieve(i64 x) {
    for (int i = 1; (i64)i * i <= x; ++i) if (x % i == 0) d.push_back(i), d.push_back(x / i);
  }
  int count(int l, int r) { // calc 26^(l - tot) + 26^(l - tot + 1) + ... + 26^(r - tot)
    if (l > r) return 0;
    l -= p.size();
    r -= p.size();
    int res = power(26, l);
    static const int inv = power(25, MOD - 2);
    int temp = (power(26, r - l + 1) - 1LL) * inv % MOD;
    return (i64)res * temp % MOD;
  }
  int solve(int s) {
    std::map<int, char> cur;
    for (int i = 0; i < p.size(); ++i) {
      int x = p[i] % s;
      if (cur.count(x) && cur[x] != q[i]) return 0;
      cur[x] = q[i];
    }
    return power(26, s - cur.size()); // the answer
  }
 public:
  int countGenerators(vector<string> s, int w, int x, int y) {
    for (int i = 0; i < s.size(); ++i) {
      q += s[i];
      for (int j = 0; j < s[i].length(); ++j) p.push_back(((i64)x + i) * w + (y + j));
    }
    n = q.length();
    for (int i = 0; i < n; ++i) sieve(llabs(p[i] - p[0])), sieve(llabs(p[i] - p[s[0].length() - 1]));
    d.push_back(w);
    std::sort(d.begin(), d.end());
    d.erase(std::unique(d.begin(), d.end()), d.end());
    while (!d.empty() && d.back() > w) d.pop_back();
    // all special values
    int res = 0;
    for (int i = 0, t = 0; i < d.size(); t = d[i++]) (res += count(t + 1, d[i] - 1)) %= MOD; // calculate the 'normal' answers
    for (int i = 0; i < d.size(); ++i) (res += solve(d[i])) %= MOD;
    return res;
  }
};
