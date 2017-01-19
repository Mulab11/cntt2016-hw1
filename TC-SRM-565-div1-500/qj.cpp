#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class TheDivisionGame {
  static const int N = 1000000 + 10;
  int sg[N];
  // sg(x) = number of x's prime factors
  // could be proved by induction
 public:
  i64 countWinningIntervals(int l, int r) {
    memset(sg, 0, sizeof sg);
    static int temp[N];
    for (int i = l; i <= r; ++i) temp[i - l] = i;
    for (int i = 2; i * i <= r; ++i)
      for (int j = (l + i - 1) / i * i; j <= r; j += i)
        for (; temp[j - l] % i == 0; temp[j - l] /= i) ++sg[j - l];
    for (int i = l; i <= r; ++i) if (temp[i - l] > 1) ++sg[i - l];
    int cnt[128];
    memset(cnt, 0, sizeof cnt);
    cnt[0] = 1;
    i64 res = r - l + 1;
    res = res * (res + 1) / 2;
    for (int i = l, j = 0; i <= r; ++i) res -= cnt[j ^= sg[i - l]]++;
    return res;
  }
};
