#include <bits/stdc++.h>

using namespace std;

class CosmicBlocks {
  std::vector<int> a, mask, e;
  int n, l, r;
  int ans;
  bool check(int p, int s, int e) {
    if (!p) return true;
    // Hall's theorem
    // p : previous, s : cur
    // e : edge
    std::vector<int> x, y;
    for (int i = 0; i < n; ++i) if (p >> i & 1) x.push_back(a[i]); else if (s >> i & 1) y.push_back(a[i]);
    std::vector<int> adj(1 << y.size());
    for (int i = 0; i < y.size(); ++i) {
      int cur = adj[1 << i] = (e & ((1 << x.size()) - 1));
      for (int j = 0; j < x.size(); ++j) if (cur >> j & 1) --x[j], --y[i];
      e >>= x.size();
    }
    for (int i = 0; i < x.size(); ++i) if (x[i] < 0) return false;
    for (int i = 0; i < y.size(); ++i) if (y[i] < 0) return false;
    std::vector<int> sx(1 << x.size()), sy(1 << y.size());
    for (int i = 0; i < x.size(); ++i) sx[1 << i] = x[i];
    for (int i = 0; i < y.size(); ++i) sy[1 << i] = y[i];
    for (int i = 1; i < sx.size(); ++i) {
      int j = i & -i;
      sx[i] = sx[j] + sx[i ^ j];
    }
    for (int i = 1; i < sy.size(); ++i) {
      int j = i & -i;
      sy[i] = sy[j] + sy[i ^ j];
      adj[i] = adj[j] | adj[i ^ j];
    }
    for (int i = 0; i < sy.size(); ++i) if (sx[adj[i]] < sy[i]) return false;
    return true;
  }
  int solve() {
    std::vector<int> f(1 << n), adj(n);
    for (int i = 1; i < mask.size(); ++i) {
      int s = mask[i - 1], t = mask[i];
      int x = e[i];
      for (int b = 0; b < n; ++b) {
        if (!(t >> b & 1)) continue;
        for (int a = 0; a < n; ++a) {
          if (!(s >> a & 1)) continue;
          if (x & 1) adj[a] |= 1 << b;
          x >>= 1;
        }
      }
    }
    f[0] = 1;
    for (int s = 0; s < (1 << n); ++s) {
      if (!f[s]) continue;
      for (int i = 0; i < n; ++i) {
        if (s >> i & 1) continue;
        if ((adj[i] & s) != adj[i]) continue;
        f[s | (1 << i)] += f[s];
      }
    }
    return f[(1 << n) - 1];
  }
  void dfs(int rem) {
    if (!rem) {
      int t = solve();
      if (l <= t && t <= r) ++ans;
      return;
    }
    for (int s = rem; s; s = (s - 1) & rem) {
      int p = (mask.empty() ? 0 : mask.back()), a = __builtin_popcount(p), b = __builtin_popcount(s);
      mask.push_back(s);
      for (int t = 0; t < (1 << (a * b)); ++t) {
        if (!check(p, s, t)) continue;
        e.push_back(t);
        dfs(rem ^ s);
        e.pop_back();
      }
      mask.pop_back();
    }
  }
 public:
  int getNumOrders(vector<int> _a, int _l, int _r) {
    a = _a, l = _l, r = _r;
    ans = 0;
    n = a.size();
    dfs((1 << n) - 1);
    return ans;
  }
};
