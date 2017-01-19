#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 40, M = 1300, MOD = 1000000007;

class LISNumber {
  int f[N][M];
  int binom[M][M];
  inline void add(int &lhs, i64 rhs) { lhs = (lhs + rhs) % MOD; }
 public:
  int count(vector<int> a, int k) {
    memset(binom, 0, sizeof binom);
    binom[0][0] = 1;
    for (int i = 1; i < M; ++i)
      for (int j = 0; j < M; ++j)
        binom[i][j] = (binom[i - 1][j] + (j ? binom[i - 1][j - 1] : 0)) % MOD;
    const int n = a.size();
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    for (int i = 0, sum = 0; i < n; sum += a[i++]) {
      for (int j = 0; j <= k; ++j) {
        // adding i, the sequence can be divided into j segments
        int cur = f[i][j];
        if (!cur) continue;
        for (int x = std::max(j + a[i] - k, 0); x <= j && x <= a[i]; ++x)
          // x 'i' are added after the j segments
          add(f[i + 1][j + a[i] - x], (i64)binom[j][x] * binom[sum - (j - x) + a[i] - x][a[i] - x] % MOD * cur);
      }
    }
    return f[n][k];
  }
};
