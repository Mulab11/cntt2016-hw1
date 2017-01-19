#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 10, MOD = 1000000007;

class TrafficCongestion {
  int f[N], g[N];
 public:
  int theMinCars(int n) {
    f[0] = f[1] = 1;
    g[0] = 1, g[1] = 2;
    // g is the prefix sum of f
    // f[i] = 2 g[i - 2] + 1
    for (int i = 2; i <= n; ++i) g[i] = (g[i - 1] + (f[i] = (2LL * g[i - 2] + 1) % MOD)) % MOD;
    return f[n];
  }
};
