#include <bits/stdc++.h>

using namespace std;

class EllysBulls {
  static const int N = 500000 + 10, M = 10;
  int n, m, tot, next[N][10], cnt[N], mem[N];
  std::vector<std::string> a;
  std::vector<int> adj[M][M];
  std::string cur;
  void insert(int v) {
    // trie
    int p = 1;
    for (int i = 0; i < n; ++i) {
      if (!next[p][cur[i]]) next[p][cur[i]] = ++tot;
      p = next[p][cur[i]];
    }
    ++cnt[p];
    mem[p] = v;
  }
  int t;
  void dfs(int i, int v = 0) {
    if (i == t) {
      insert(v);
      return;
    }
    for (int j = 0; j < 10; ++j) {
      for (int k = 0; k < adj[i][j].size(); ++k) ++cur[adj[i][j][k]];
      dfs(i + 1, 10 * v + j);
      for (int k = 0; k < adj[i][j].size(); ++k) --cur[adj[i][j][k]];
    }
  }
  std::string ans;
  int val;
  void query(int v) {
    // combine the two parts
    int p = 1;
    for (int i = 0; i < n; ++i) p = next[p][cur[i]];
    if (cnt[p]) {
      val += cnt[p];
      if (val == 1) {
        std::stringstream ss;
        ss << setfill('0') << setw(t) << mem[p];
        ss << setw(m - t) << v;
        ans = ss.str();
      }
    }
  }
  void dfs2(int i, int v = 0) {
    if (i == m) {
      query(v);
      return;
    }
    for (int j = 0; j < 10; ++j) {
      bool flag = true;
      for (int k = 0; k < adj[i][j].size(); ++k) if (--cur[adj[i][j][k]] < 0) flag = false;
      if (flag) dfs2(i + 1, 10 * v + j);
      for (int k = 0; k < adj[i][j].size(); ++k) ++cur[adj[i][j][k]];
    }
  }
 public:
  string getNumber(vector<string> _a, vector<int> b) {
    a = _a;
    n = a.size(), m = a[0].length();
    t = m / 2;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        adj[j][a[i][j] - '0'].push_back(i);
    cur.resize(n);
    for (int i = 0; i < n; ++i) cur[i] = 0;
    memset(next, 0, sizeof next);
    tot = 1;
    // meet-in-the-middle
    dfs(0);
    for (int i = 0; i < n; ++i) cur[i] = b[i];
    dfs2(t);
    if (val == 0) return "Liar";
    if (val > 1) return "Ambiguity";
    return ans;
  }
};
