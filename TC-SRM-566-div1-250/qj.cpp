#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class PenguinSledding {
  static const int N = 50 + 10;
  bool adj[N][N];
 public:
  i64 countDesigns(int n, vector<int> a, vector<int> b) {
    std::vector<int> cnt(n);
    for (int i = 0; i < a.size(); ++i) ++cnt[a[i] - 1], ++cnt[b[i] - 1];
    i64 res = 0;
    for (int i = 0; i < n; ++i) res += (1LL << cnt[i]) - 1;
    res -= a.size();
    ++res;
    memset(adj, 0, sizeof adj);
    for (int i = 0; i < a.size(); ++i) adj[a[i]][b[i]] = adj[b[i]][a[i]] = true;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j < i; ++j)
        for (int k = 1; k < j; ++k)
          if (adj[i][j] && adj[j][k] && adj[i][k]) ++res;
    return res;
  }
};
