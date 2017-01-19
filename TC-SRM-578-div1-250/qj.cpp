#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 50 + 10, MOD = 1000000007;

class GooseInZooDivOne {
  int anc[N * N], size[N * N];
  int find(int x) { return anc[x] == x ? x : (anc[x] = find(anc[x])); }
  void meld(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    anc[x] = y;
    size[y] += size[x];
  }
 public:
  int count(vector<string> s, int d) {
    const int n = s.size(), m = s[0].length();
    for (int i = 0; i < n * m; ++i) anc[i] = i, size[i] = (s[i / m][i % m] == 'v');
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (s[i][j] == '.') continue;
        for (int x = 0; x < n; ++x)
          for (int y = 0; y < m; ++y)
            if (s[x][y] == 'v' && abs(x - i) + abs(y - j) <= d) meld(x * m + y, i * m + j); // merge the birds
      }
    }
    std::vector<int> cnt(2);
    for (int i = 0; i < n * m; ++i) if (find(i) == i && size[i]) ++cnt[size[i] & 1]; // sort out all groups by parity
    int res = 1;
    for (int i = cnt[0] + std::max(cnt[1] - 1, 0); i--;) res = 2LL * res % MOD;
    res = (res + MOD - 1) % MOD;
    return res;
  }
};
