#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class ConversionMachine {
  static const int M = 12, N = M * M, MOD = 1000000007;
  void mul(int lhs[][N], const int rhs[][N]) {
    static int res[N][N];
    memset(res, 0, sizeof res);
    for (int i = 0; i < N; ++i)
      for (int k = 0; k < N; ++k)
        for (int j = 0; j < N; ++j)
          res[i][j] = (res[i][j] + (i64)lhs[i][k] * rhs[k][j]) % MOD;
    memcpy(lhs, res, sizeof res);
  }
  inline int pos(int x, int y) { return x * M + y; }
  int trans[N][N], res[N][N];
 public:
  int countAll(string s, string t, vector<int> a, int m) {
    int cnt = 0;
    const int n = s.length();
    for (int i = 0; i < n; ++i) s[i] -= 'a', t[i] -= 'a';
    int x = 0, y = 0;
    for (int i = 0; i < n; ++i) {
      int c = s[i], z = 0;
      for (; c != t[i]; c = (c + 1) % 3) {
        ++cnt, ++z;
        if ((m -= a[c]) < 0) return 0;
      }
      if (z == 1) ++x; else if (z == 2) ++y;
    }
    cnt += m / (a[0] + a[1] + a[2]) * 3;
    // cnt is just the number of steps we need to go
    memset(trans, 0, sizeof trans);
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; i + j <= n; ++j) {
        int k = n - i - j, a = pos(i, j);
        if (i) (trans[a][pos(i - 1, j)] += i) %= MOD;
        if (j) (trans[a][pos(i + 1, j - 1)] += j) %= MOD;
        if (k) (trans[a][pos(i, j + 1)] += k) %= MOD;
      }
    }
    trans[0][N - 1] = trans[N - 1][N - 1] = 1;
    memset(res, 0, sizeof res);
    for (int i = 0; i < N; ++i) res[i][i] = 1;
    for (int exp = cnt + 1; exp; exp >>= 1) {
      if (exp & 1) mul(res, trans);
      mul(trans, trans);
    }
    return res[pos(x, y)][N - 1];
  }
};
