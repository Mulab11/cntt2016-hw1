#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class PyramidSequences {
  int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
 public:
  i64 distinctPairs(int n, int m) {
    // hint: plot all points in an xy-coordinate plane, then find the pattern
    // see https://apps.topcoder.com/wiki/display/tc/SRM+591 for a figure and further explanation
    --n, --m;
    int t = gcd(n, m);
    n /= t, m /= t;
    i64 res = (i64)n * m * (t - 1);
    res += (m / 2 + 1LL) * (n / 2 + 1LL);
    res += ((m + 1LL) / 2) * ((n + 1LL) / 2);
    return res;
  }
};
