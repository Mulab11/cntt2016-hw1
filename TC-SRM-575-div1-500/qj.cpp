#include <bits/stdc++.h>

using namespace std;

class TheSwapsDivOne {
  std::string s;
  inline double calc(int x) { return x * (x - 1.) / 2.; } // C(n, 2)
  void mul(double lhs[][2], const double rhs[][2]) { // matrix multiplication
    double res[2][2];
    res[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
    res[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];
    res[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
    res[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];
    memcpy(lhs, res, sizeof res);
  }
  void power(double base[][2], int exp) {
    double res[2][2] = {{1., 0.}, {0., 1.}};
    for (; exp; exp >>= 1) {
      if (exp & 1) mul(res, base);
      mul(base, base);
    }
    memcpy(base, res, sizeof res);
  }
 public:
  double find(vector<string> _s, int k) {
    for (int i = 0; i < _s.size(); ++i) s += _s[i];
    const int n = s.length();
    double res = 0.;
    for (int i = 1; i <= n; ++i) {
      double a[2][2];
      a[0][1] = i / calc(n);
      a[1][0] = (n - i) / calc(n);
      a[0][0] = 1. - a[0][1];
      a[1][1] = 1. - a[1][0];
      power(a, k);
      for (int j = 0; j < n; ++j) {
        // calculate the expectation that j is finally put at position i
        // k + i - 1 == j
        // k == j - i + 1
        int l = std::max(j - i + 1, 0), r = std::min(j, n - i);
        int t = r - l + 1;
        res += (s[j] - '0') * ((n - i + 1 - t) * a[0][1] + t * a[1][1]);
      }
    }
    res /= calc(n + 1); // number of distinct contiguous subsequences
    return res;
  }
};
