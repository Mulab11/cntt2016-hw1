#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class HolyNumbers {
  static const int N = 1000000 + 10;
  int p[N], cnt;
  void sieve(int n) {
    cnt = 0;
    static bool flag[N];
    std::fill(flag, flag + n + 1, false);
    for (int i = 2; i <= n; ++i) {
      if (!flag[i]) p[cnt++] = i;
      for (int j = 0; j < cnt && i * p[j] <= n; ++j) {
        flag[i * p[j]] = true;
        if (i % p[j] == 0) break;
      }
    }
  }
  i64 ans;
  void dfs(int i, i64 cur) {
    if (i == cnt || p[i] > cur) {
      ++ans;
      return;
    }
    if ((i64)p[i] * p[i + 1] > cur) {
      // this saves a lot of computations
      ans += std::upper_bound(p + i, p + cnt, cur) - p - i + 1;
      return;
    }
    dfs(i + 1, cur);
    for (cur /= p[i]; cur; cur /= (i64)p[i] * p[i]) dfs(i + 1, cur);
  }
 public:
  i64 count(i64 n, int m) {
    sieve(m);
    ans = 0;
    dfs(0, n);
    return ans;
  }
};
