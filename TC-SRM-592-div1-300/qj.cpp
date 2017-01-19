#include <bits/stdc++.h>

using namespace std;

class LittleElephantAndBalls {
  int dispatch(char c) {
    if (c == 'R') return 1;
    if (c == 'G') return 2;
    return 4;
  }
  int solve(std::string &s, char c) {
    // greedy
    const int n = s.length();
    std::vector<int> pre(n + 1), suf(n + 1);
    for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] | dispatch(s[i]);
    for (int i = n - 1; i >= 0; --i) suf[i] = suf[i + 1] | dispatch(s[i]);
    int res = 0, p = 0;
    for (int i = 0; i <= n; ++i) {
      int t = __builtin_popcount(pre[i]) + __builtin_popcount(suf[i]);
      if (t >= res) res = t, p = i;
    }
    s.insert(p, 1, c);
    return res;
  }
 public:
  int getNumber(string s) {
    std::string cur;
    int res = 0;
    for (int i = 0; i < s.length(); ++i) res += solve(cur, s[i]);
    return res;
  }
};
