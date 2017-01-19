#include <bits/stdc++.h>

using namespace std;

class Stamp {
  static const int N = 50 + 10, INF = 0x3f3f3f3f;
  inline void check(int &lhs, int rhs) { if (rhs < lhs) lhs = rhs; }
 public:
  int getMinimumCost(string s, int a, int b) {
    int ans = INF;
    const int n = s.length();
    for (int i = 1; i <= n; ++i) {
      static int f[N];
      memset(f, 0x3f, sizeof f);
      f[0] = 0;
      for (int j = 0; j < n; ++j) {
        char c = '*';
        for (int k = j; k < n; ++k) {
          if (s[k] != '*') {
            if (c != '*' && s[k] != c) break;
            c = s[k];
          }
          if (k - j + 1 >= i) check(f[k + 1], f[j] + (k - j + i) / i * b); // full
        }
      }
      check(ans, f[n] + i * a);
    }
    return ans;
  }
};
