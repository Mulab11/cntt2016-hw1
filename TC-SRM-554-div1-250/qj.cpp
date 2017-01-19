#include <bits/stdc++.h>

using namespace std;

class TheBrickTowerEasyDivOne {
 public:
  int find(int a, int b, int x, int y) {
    if (a > x) std::swap(a, x), std::swap(b, y);
    x = std::min(x, a + 1);
    return b == y ? (a + x) : (3 * a + (a != x));
  }
};
