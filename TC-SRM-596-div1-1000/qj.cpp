#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 1000000 + 10;

class SparseFactorial {
  std::vector<i64> mem[N], ans;
  i64 n, m;
  void solve(i64 p, i64 c, i64 q) {
    // d = q = p^c
    for (int i = 0; i < p; ++i) mem[i].clear();
    for (int i = 0; i < q; ++i) mem[(i64)i * i % p].push_back((i64)i * i);
    for (int i = 0; i < q; ++i) {
      int j = i % p;
      if (mem[j].empty()) {
        for (int k = i; k < m; k += q) ans[k] = std::max(ans[k], n);
      } else {
        int val = 1;
        for (bool flag = false; !flag;) {
          for (int b = 0; b < mem[j].size(); ++b) {
            val = (i64)val * (i - mem[j][b] % q) % q;
            if (val == 0) {
              flag = true;
              for (int k = i; k < m; k += q) ans[k] = std::max(ans[k], mem[j][b]);
              break;
            }
          }
        }
      }
    }
  }
  i64 calc(i64 r, i64 y) {
    // number of integers x in [y, r) such that x = y (mod d)
    r -= y;
    if (r < 0) return 0;
    return r / m + 1;
  }
 public:
  i64 getCount(i64 l, i64 r, i64 _m) {
    // Let ans[i] be the minimal y, such that f(y * d + i) mod d = 0.
    // With ans[] one can easily calculate the answer.
    // To calculate ans[x], we could factorize d.
    // For some d = p^c, we could sort out i \in [0, p) by i^2 mod p, then we only consider i that x \equiv i^2 (mod p), and we enumerate these i. (We would only enumerate over O(c) elements.)
    m = _m;
    n = r + 1;
    ans.resize(m);
    for (i64 i = 2, s = m; i <= s; ++i) {
      i64 p = i, c = 0;
      for (; s % i == 0; s /= i) ++c;
      if (c) {
        i64 q = 1;
        for (int t = c; t--;) q *= i;
        solve(p, c, q);
      }
    }
    i64 res = 0;
    for (int i = 0; i < m; ++i) {
      i64 t = ans[i] / m * m + i;
      if (t <= ans[i]) t += m;
      res += calc(r, t) - calc(l - 1, t);
    }
    return res;
  }
};
