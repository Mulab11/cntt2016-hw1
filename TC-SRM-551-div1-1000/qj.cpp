#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class SweetFruits {
  static const int N = 50, MOD = 1000000007;
  void calc(const std::vector<int> &a, std::vector<int> res[]) {
    const int n = a.size(), m = 1 << n;
    for (int i = 0; i <= n; ++i) res[i].clear();
    std::vector<int> cur(m), cnt(m);
    cur[0] = 0;
    for (int i = 0; i < n; ++i) cur[1 << i] = a[i];
    res[0].push_back(0);
    for (int i = 1; i < m; ++i) {
      int j = i & -i;
      cur[i] = cur[j] + cur[i ^ j];
      cnt[i] = cnt[i >> 1] + (i & 1);
      res[cnt[i]].push_back(cur[i]);
    }
  }
  std::vector<int> solve(const std::vector<int> &a, int m) {
    const int n = a.size();
    std::vector<int> p[N], q[N];
    calc(std::vector<int>(a.begin(), a.begin() + n / 2), p);
    calc(std::vector<int>(a.begin() + n / 2, a.end()), q);
    for (int i = 0; i < N; ++i) {
      std::sort(p[i].begin(), p[i].end());
      std::sort(q[i].begin(), q[i].end());
    }
    std::vector<int> res(n + 1);
    for (int i = 0; i <= n; ++i) {
      // meet-in-the-middle
      if (p[i].empty()) continue;
      for (int j = 0; i + j <= n; ++j) {
        if (q[j].empty()) continue;
        for (int a = 0, b = q[j].size() - 1; b >= 0 && a < p[i].size(); ++a) {
          while (b >= 0 && q[j][b] + p[i][a] > m) --b;
          (res[i + j] += b + 1) %= MOD;
        }
      }
    }
    return res;
  }
  int inv(int x) { return x == 1 ? 1 : (((i64)MOD - MOD / x) * inv(MOD % x) % MOD); }
  int det(int a[][N], int k) {
    // determinant of a k x k matrix
    int res = 1;
    for (int i = 0; i < k; ++i) {
      for (int j = i; j < k; ++j) {
        if (a[j][i]) {
          for (int t = 0; t < k; ++t) std::swap(a[i][t], a[j][t]);
          if (i != j) res = -res;
          break;
        }
      }
      if (!a[i][i]) return 0;
      for (int j = i + 1; j < k; ++j) {
        int t = (i64)a[j][i] * inv(a[i][i]) % MOD;
        if (t) for (int q = 0; q < k; ++q) a[j][q] = (a[j][q] - (i64)a[i][q] * t) % MOD;
      }
    }
    for (int i = 0; i < k; ++i) res = (i64)res * a[i][i] % MOD;
    return (res + MOD) % MOD;
  }
  std::vector<int> kirchoff(int n, int m) {
    // Kirchoff's theorem
    std::vector<int> res(n + 1);
    for (int i = 0; i <= n; ++i) {
      static int a[N][N];
      memset(a, 0, sizeof a);
      for (int x = 0; x < i; ++x) {
        for (int y = 0; y < x; ++y) {
          ++a[x][x], ++a[y][y];
          --a[x][y], --a[y][x];
        }
      }
      for (int x = 0; x < n + m; ++x) {
        for (int y = std::max(n, x + 1); y < n + m; ++y) {
          ++a[x][x], ++a[y][y];
          --a[x][y], --a[y][x];
        }
      }
      res[i] = det(a, n + m - 1);
    }
    static int binom[N][N];
    memset(binom, 0, sizeof binom);
    binom[0][0] = 1;
    for (int i = 1; i < N; ++i)
      for (int j = 0; j < N; ++j)
        binom[i][j] = (binom[i - 1][j] + (j ? binom[i - 1][j - 1] : 0)) % MOD;
    for (int i = 1; i <= n; ++i)
      for (int j = 0; j < i; ++j)
        res[i] = (res[i] - (i64)binom[i][j] * res[j]) % MOD;
    return res;
  }
 public:
  int countTrees(vector<int> a, int m) {
    int cnt = 0;
    std::vector<int> b;
    for (int i = 0; i < a.size(); ++i) if (a[i] == -1) ++cnt; else b.push_back(a[i]);
    const int n = b.size();
    std::vector<int> x = solve(b, m), y = kirchoff(n, cnt);
    int res = 0;
    for (int i = 0; i <= n; ++i) res = (res + (i64)x[i] * y[i]) % MOD; // combine these two parts
    return (res + MOD) % MOD;
  }
};
