#include <bits/stdc++.h>

using namespace std;

class FoxAndMountainEasy {
 public:
  string possible(int n, int a, int b, string s) {
    int c = 0, d = 0;
    for (int i = 0; i < s.length(); ++i, c = std::min(c, d)) if (s[i] == 'U') ++d; else --d;
    n -= s.length();
    int m = b - a;
    m -= d;
    n -= abs(m);
    if (n < 0 || (n & 1)) return "NO";
    int x = n / 2 + std::max(m, 0);
    if (a + x + c < 0) return "NO";
    return "YES";
  }
};
