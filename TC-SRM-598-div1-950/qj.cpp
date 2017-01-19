#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10;

class TPS {
  int n;
  std::vector<std::string> adj;
  int mem[N][N];
  int dfs(int a, int fa) {
    // If vertex a has k sons, in order to distinguish from them, at lease k-1 of them should have a beacon in their subtree.
    int &res = mem[a][fa];
    if (res != -1) return res;
    int sum = 0, det = 0;
    for (int b = 0; b < n; ++b) {
      if (adj[a][b] == 'N' || b == fa) continue;
      int x = dfs(b, a), y = std::max(x, 1);
      sum += y;
      det = std::min(det, x - y);
    }
    return res = sum + det;
  }
 public:
  int minimalBeacons(vector<string> _adj) {
    adj = _adj;
    n = adj.size();
    if (n == 1) return 0;
    int res = n;
    memset(mem, -1, sizeof mem);
    // Enumerate the position of one of the beacons.
    // Then DP.
    for (int i = 0; i < n; ++i) res = std::min(res, dfs(i, n) + 1);
    return res;
  }
};
