#include <bits/stdc++.h>

using namespace std;

class XorTravelingSalesman {
  static const int N = 50 + 10;
 public:
  int maxProfit(vector<int> b, vector<string> a) {
    // just do BFS
    const int n = b.size();
    static int q[N << 11];
    static bool flag[N][1 << 10];
    memset(flag, 0, sizeof flag);
    flag[0][b[0]] = true;
    int ans = 0;
    q[1] = 0, q[2] = b[0];
    for (int i = 1, r = 2; i <= r; i += 2) {
      int x = q[i], y = q[i + 1];
      ans = std::max(ans, y);
      for (int u = 0; u < n; ++u) {
        if (a[x][u] == 'N') continue;
        int v = y ^ b[u];
        if (!flag[u][v]) flag[u][v] = true, q[++r] = u, q[++r] = v;
      }
    }
    return ans;
  }
};
