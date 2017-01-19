#include <bits/stdc++.h>

using namespace std;

class TheSquareRootDilemma {
  static const int N = 100000 + 10;
  int cnt[N];
 public:
  int countPairs(int n, int m) {
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i * i <= m; ++i) cnt[i * i] = 1;
    for (int i = 1; i < N; ++i) cnt[i] += cnt[i - 1]; // number of square numbers
    int res = 0;
    for (int a = 1; a <= n; ++a) {
      int x = a, b = 1;
      for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
          int cnt = 0;
          for (; x % i == 0; x /= i) ++cnt;
          if (cnt & 1) b *= i;
        }
      }
      if (x > 1) b *= x;
      // b is the product of square free prime factors
      res += cnt[m / b];
    }
    return res;
  }
};
