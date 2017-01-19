#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 2500 + 10;

int n;

class BIT {
  int data[N];
 public:
  inline void clear() { memset(data, 0, sizeof data); }
  BIT() { clear(); }
  inline void add(int p, int v) { for (++p; p <= n + 1; p += p & -p) data[p] += v; }
  inline int query(int p) {
    int res = 0;
    for (p = std::min(p, n) + 1; p; p ^= p & -p) res += data[p];
    return res;
  }
};

class LittleElephantAndRGB {
  BIT bit;
 public:
  i64 getNumber(vector<string> list, int m) {
    std::string s;
    for (int i = 0; i < list.size(); ++i) s += list[i];
    n = s.length();
    i64 res = 0;
    for (int b = n - 2; b >= 0; --b) { // enumerate b
      const int c = b + 1;
      int ls = 0, rs = 0, mx = 0;
      for (int d = c; d < n; ++d) {
        if (s[d] == 'G') {
          mx = std::max(mx, ++rs);
          if (rs == d - c + 1) ++ls;
        } else {
          rs = 0;
        }
        if (mx < m) bit.add(ls, 1);
      }
      ls = rs = mx = 0;
      int tot = n - b - 1;
      tot = tot * (tot + 1) / 2;
      for (int a = b; a >= 0; --a) { // enumerate a
        if (s[a] == 'G') {
          mx = std::max(mx, ++ls); // length of LCS = max(s.ms, t.ms, s.rs + t.ls)
          if (ls == b - a + 1) ++rs;
        } else {
          ls = 0;
        }
        res += tot;
        if (mx < m) res -= bit.query(m - rs - 1); // subtract illegal LCS
      }
    }
    return res;
  }
};
