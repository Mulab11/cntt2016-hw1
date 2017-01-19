#include <bits/stdc++.h>

using namespace std;

const int N = 300 + 10, MOD = 1000000007;

class WolfInZooDivOne {
  std::vector<int> parse(const std::vector<std::string> &pool) {
    std::string s;
    for (int i = 0; i < pool.size(); ++i) s += pool[i];
    std::stringstream ss(s);
    std::vector<int> res;
    for (int x; ss >> x;) res.push_back(x);
    return res;
  }
  int f[N][N];
 public:
  int count(int n, vector<string> _l, vector<string> _r) {
    std::vector<int> l = parse(_l), r = parse(_r);
    const int m = l.size();
    memset(f, 0, sizeof f);
    std::vector<int> tag(n, 0);
    for (int i = 0; i < m; ++i)
      for (int j = l[i]; j <= r[i]; ++j)
        tag[j] = std::max(tag[j], r[i] + 1);
    // tag[i]: if we put 1 at i-th position, then interval [i + 1, tag[i]) must contain at most one 1
    f[0][0] = 1;
    // f[i][j]:
    //   we are at position i
    //   there must be at most one 1 in interval [i, j)
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= n; ++j) {
        int cur = f[i][j];
        if (!cur) continue;
        (f[i + 1][j] += cur) %= MOD;
        (f[std::max(j, i + 1)][tag[i]] += cur) %= MOD;
      }
    }
    int res = 0;
    for (int i = 0; i <= n; ++i) (res += f[n][i]) %= MOD;
    return res;
  }
};
