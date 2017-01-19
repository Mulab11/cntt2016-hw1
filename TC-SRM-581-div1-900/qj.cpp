#include <bits/stdc++.h>

using namespace std;

class YetAnotherBoardGame {
  static const int N = 14, INF = 0x3f3f3f3f;
  int n, m, mask[N];
  int solve(int s1, int s2, int s) {
    const int f = (1 << m) - 1;
    static int cur[N];
    memset(cur, 0, sizeof cur);
    cur[0] = ((s >> 1) ^ (s << 1)) & f;
    if (s & s2) cur[0] ^= s;
    cur[1] = s;
    int res = __builtin_popcount(s);
    for (int i = 1; i < n; ++i) {
      int t = cur[i - 1] ^ mask[i - 1];
      // we can imply the state of current row from previous rows
      if ((t & s1) && (t & s2)) return INF;
      res += __builtin_popcount(t);
      int x = (t >> 1) ^ (t << 1);
      if (t & s2) x ^= t;
      x &= f;
      cur[i] ^= x;
      cur[i - 1] ^= t;
      cur[i + 1] ^= t;
    }
    for (int i = 0; i < n; ++i) if (cur[i] != mask[i]) return INF; // check if our operation is legal
    return res;
  }
 public:
  int minimumMoves(vector<string> a) {
    memset(mask, 0, sizeof mask);
    n = a.size(), m = a[0].length();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (a[i][j] == 'W') mask[i] |= 1 << j;
    int res = INF;
    for (int s1 = 0, f = (1 << m) - 1; s1 < (1 << m); ++s1) {
      int s2 = s1 ^ f;
      // s1 : operation 1 only
      // s2 : operation 2 only
      // then we enumerate the state of the first row
      for (int s = s1; s; s = (s - 1) & s1) res = std::min(res, solve(s1, s2, s));
      for (int s = s2; s; s = (s - 1) & s2) res = std::min(res, solve(s1, s2, s));
      res = std::min(res, solve(s1, s2, 0));
    }
    return res == INF ? -1 : res;
  }
};
