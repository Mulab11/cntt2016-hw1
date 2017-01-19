#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class BigFatInteger {
  int solve(int x) {
    int cur = 1, res = 0;
    for (; x; ++res) {
      int y = std::min(cur, x);
      cur += y;
      x -= y;
    }
    return res;
  }
 public:
  int minOperations(int a, int b) {
    // if a is a prime, we could use greedy method: that is, at first we let x = a, then every time we let x = min(x^2, a^b),
    // otherwise, we could factor a into several powers of prime, then use the method above.
    std::vector<i64> pool;
    int res = 0;
    for (int i = 2; i <= a; ++i) {
      if (a % i == 0) {
        i64 cnt = 0;
        for (; a % i == 0; a /= i) ++cnt;
        cnt *= b;
        ++res;
        if (cnt > 1) pool.push_back(cnt - 1);
      }
    }
    int cur = 0;
    for (int i = 0; i < pool.size(); ++i) cur = std::max(cur, solve(pool[i]));
    return res += cur;
  }
};
