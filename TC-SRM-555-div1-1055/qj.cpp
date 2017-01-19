#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class MapGuessing {
  static const int N = 40;
  int n, m, tot;
  std::string s, t;
  std::vector<i64> mask;
  i64 sim(int p) { // simulate the process
    i64 res = 0, cur = 0;
    std::string temp = s;
    int cnt = n;
    for (int i = 0; i < m; ++i) {
      if (isdigit(t[i])) {
        cnt -= (temp[p] == s[p]);
        temp[p] = t[i];
        cnt += (temp[p] == s[p]);
        cur |= 1LL << p;
        if (cnt == n) res = cur;
      } else {
        if (t[i] == '<') --p; else ++p;
        if (!(0 <= p && p < n)) return -1;
      }
    }
    return res;
  }
  i64 ans;
  void dfs(int i, int j, i64 cur) {
    if (!cur) {
      if (i == mask.size()) {
        if (j & 1) ++ans; else --ans;
      }
      return;
    }
    int k = __builtin_popcountll(cur);
    if (i == mask.size()) {
      if (!j) return;
      if (j & 1) ans += 1LL << k; else ans -= 1LL << k;
      return;
    }
    dfs(i + 1, j, cur);
    dfs(i + 1, j + 1, cur & mask[i]);
  }
 public:
  i64 countPatterns(string _s, vector<string> pool) {
    s = _s;
    for (int i = 0; i < pool.size(); ++i) t += pool[i];
    n = s.length(), m = t.length();
    for (int i = 0; i < n; ++i) {
      i64 x = sim(i);
      if (x != -1) mask.push_back(x);
    }
    ans = 0;
    dfs(0, 0, (1LL << n) - 1);
    return ans;
  }
};
