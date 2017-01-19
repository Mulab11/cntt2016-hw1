#include <bits/stdc++.h>

using namespace std;

class JumpFurther {
 public:
  int furthest(int n, int m) {
    int res = 0;
    for (int i = 1; i <= n; ++i) if ((res += i) == m) --res; // just follow the problem
    return res;
  }
};
