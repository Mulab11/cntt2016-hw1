#include <bits/stdc++.h>

using namespace std;

class DSU {
  static const int N = 50 + 10;
 public:
  int anc[N];
  bool col[N];
  int find(int x) {
    if (anc[x] == x) return x;
    int y = find(anc[x]);
    col[x] ^= col[anc[x]];
    return anc[x] = y;
  }
  void clear(int n) {
    for (int i = 0; i < n; ++i) col[anc[i] = i] = 0;
  }
  bool meld(int x, int y, bool z) {
    // maintain a bipartite graph
    // z : whether col[x] == col[y]
    int a = find(x), b = find(y);
    if (a == b) return (col[x] != col[y]) == z;
    anc[a] = b;
    col[a] ^= (col[x] != col[y]) != z;
    return true;
  }
};

class DisjointSemicircles {
  int n, m, tot;
  std::vector<int> a, l, r, b;
  std::vector<bool> flag;
  bool res;
  DSU dsu;
  bool check(int l1, int r1, int l2, int r2) { // check if intersect
    return (l1 <= l2 && l2 <= r1 && r1 <= r2) || (l2 <= l1 && l1 <= r2 && r2 <= r1);
  }
  void dfs1(int dep) {
    if (dep == tot / 2) {
      dsu.clear(n);
      for (int i = 0; i < l.size(); ++i)
        for (int j = 0; j < i; ++j)
          if (check(l[i], r[i], l[j], r[j]) && !dsu.meld(i, j, 1)) return;
      res = true;
      return;
    }
    int i = dep;
    while (flag[i]) ++i;
    flag[i] = true;
    l.push_back(b[i]);
    for (int j = i + 1; j < tot; ++j) {
      // enumerate the pairing
      if (flag[j]) continue;
      flag[j] = true;
      r.push_back(b[j]);
      dfs1(dep + 1);
      if (res) return;
      r.pop_back();
      flag[j] = false;
    }
    l.pop_back();
    flag[i] = false;
  }
  bool solve1() {
    for (int i = 0; i < n; ++i) if (a[i] == -1) b.push_back(i);
    flag.clear();
    flag.resize(tot = b.size());
    res = false;
    dfs1(0);
    return res;
  }
  bool solve2() {
    for (int s = 0; s < (1 << m); ++s) {
      // enumerate the directions of the pre-exists semicircles
      dsu.clear(n + 1);
      dsu.meld(0, n, 0);
      for (int i = 0; i < m; ++i) {
        bool t = s >> i & 1;
        if (!dsu.meld(l[i], l[i] + 1, t)) goto fail;
        if (!dsu.meld(r[i], r[i] + 1, t)) goto fail;
        if (!t) t ^= (r[i] - l[i]) & 1;
        if (!dsu.meld(l[i], r[i] + 1, !t)) goto fail;
      }
      for (int i = 0; i < m; ++i)
        for (int j = 0; j < i; ++j)
          if (check(l[i], r[i], l[j], r[j]) && (s >> i & 1) == (s >> j & 1)) goto fail;
      return true;
   fail:
      continue;
    }
    return false;
  }
 public:
  string getPossibility(vector<int> _a) {
    a = _a;
    n = a.size();
    m = 0;
    flag.resize(n);
    for (int i = 0; i < n; ++i) {
      if (a[i] == -1 || flag[i]) continue;
      for (int j = i + 1; j < n; ++j) {
        if (!flag[j] && a[j] == a[i]) {
          a[i] = a[j] = m++;
          flag[i] = flag[j] = true;
          l.push_back(i);
          r.push_back(j);
          break;
        }
      }
    }
    return (std::count(a.begin(), a.end(), -1) <= 12 ? solve1() : solve2()) ? "POSSIBLE" : "IMPOSSIBLE"; // meet-in-the-middle
  }
};
