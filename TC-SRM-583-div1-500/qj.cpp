#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10;

class TurnOnLamps {
  int n;
  std::vector<int> adj[N];
  bool flag[N], cur[N];
  inline void check(int &lhs, int rhs) { if (rhs < lhs) lhs = rhs; }
  int dfs(int a) {
    int res = 0;
    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i];
      res += dfs(b);
    }
    if (a && flag[a] && !(cur[a] ^ (res & 1))) ++res; // use a to adjust our solution
    return res;
  }
 public:
  int minimize(vector<int> a, string b, string c) {
    n = a.size() + 1;
    for (int i = 1; i < n; ++i) adj[a[i - 1]].push_back(i);
    for (int i = 1; i < n; ++i) cur[i] = (b[i - 1] == '1'), flag[i] = (c[i - 1] == '1');
    int res = (dfs(0) + 1) / 2; // pairing the vertices arbitrarily
    return res;
  }
};
