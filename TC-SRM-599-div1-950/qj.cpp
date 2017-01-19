#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 50 + 10, M = 8, MOD = 1000000007;

class SimilarNames {
  int n, m, fa[N];
  int tot, id[N];
  std::vector<int> adj[N];
  int f[N][1 << (2 * M)];
  bool isPrefix(const std::string &a, const std::string &b) { // check if a is a prefix of b
    if (a.length() > b.length()) return false;
    for (int i = 0; i < a.length(); ++i) if (a[i] != b[i]) return false;
    return true;
  }
  int succ[1 << (2 * M)], mask[1 << (2 * M)];
  void dfs(int a) {
    // f[i][s]: number of ways to embed i's subtree into set s and to satisify the constraints in s
    f[a][0] = 1;
    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i];
      dfs(b);
      static int temp[1 << (2 * M)];
      memcpy(temp, f[a], sizeof temp);
      for (int s = 0; s < (1 << tot); ++s) {
        if (!f[a][s]) continue;
        int u = s ^ ((1 << tot) - 1);
        for (int t = u; t; t = (t - 1) & u) {
          // use a subset convolution to merge the result
          // notice the constraint
          if (f[b][t] && !(mask[t] & s)) temp[s | t] = (temp[s | t] + (i64)f[a][s] * f[b][t]) % MOD;
        }
      }
      memcpy(f[a], temp, sizeof temp);
    }
    if (a < n) {
      for (int s = (1 << tot) - 1; s >= 0; --s) {
        for (int i = 0; i < tot; ++i) {
          if ((s >> i & 1) && !(succ[s ^ (1 << i)] >> i & 1)) (f[a][s] += f[a][s ^ (1 << i)]) %= MOD;
        }
      }
    }
  }
 public:
  int count(vector<string> s, vector<int> a, vector<int> b) {
    // construct the trie
    std::sort(s.begin(), s.end());
    n = s.size();
    m = a.size();
    for (int i = 0; i < n; ++i) {
      fa[i] = n;
      for (int j = 0; j < i; ++j) if (isPrefix(s[j], s[i])) fa[i] = j;
    }
    memset(id, -1, sizeof id);
    for (int i = 0; i < m; ++i) id[a[i]] = id[b[i]] = 0;
    tot = 0;
    for (int i = 0; i < n; ++i) if (!id[i]) id[i] = tot++;
    memset(succ, 0, sizeof succ);
    memset(mask, 0, sizeof mask);
    for (int i = 0; i < n; ++i) adj[fa[i]].push_back(i);
    for (int i = 0; i < m; ++i) a[i] = id[a[i]], b[i] = id[b[i]];
    for (int i = 0; i < m; ++i) succ[1 << a[i]] |= 1 << b[i];
    for (int i = 0; i < m; ++i) mask[1 << a[i]] |= 1 << b[i], mask[1 << b[i]] |= 1 << a[i];
    //transitive closure
    for (int s = 0; s < (1 << tot); ++s)
      for (int i = 0; i < tot; ++i)
        if (s >> i & 1) mask[s] |= mask[1 << i], succ[s] |= succ[1 << i];
    memset(f, 0, sizeof f);
    dfs(n);
    int res = f[n][(1 << tot) - 1];
    for (int i = n - tot; i; --i) res = (i64)res * i % MOD;
    return res;
  }
};
