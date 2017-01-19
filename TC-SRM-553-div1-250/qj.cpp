#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef std::pair<i64, i64> Info;

inline Info operator+ (const Info &lhs, const Info &rhs) { return Info(lhs.first + rhs.first, lhs.second + rhs.second); }

class Suminator {
  int solve1(const std::vector<int> &s, i64 m) {
    const int n = s.size();
    std::stack<i64> stk;
    for (i64 i = 100; i--;) stk.push(0);
    for (i64 i = 0; i < n; ++i) {
      if (s[i] <= 0) {
        i64 a = stk.top();
        stk.pop();
        a += stk.top();
        stk.pop();
        stk.push(a);
      } else {
        stk.push(s[i]);
      }
    }
    return stk.top() == m ? 0 : -1;
  }
  int solve2(const std::vector<int> &s, i64 m) {
    const i64 n = s.size();
    std::stack<Info> stk;
    for (i64 i = 100; i--;) stk.push(Info(0, 0));
    for (i64 i = 0; i < n; ++i) {
      if (s[i] == 0) {
        Info info = stk.top();
        stk.pop();
        info = info + stk.top();
        stk.pop();
        stk.push(info);
      } else if (s[i] == -1) {
        stk.push(Info(1, 0));
      } else {
        stk.push(Info(0, s[i]));
      }
    }
    Info info = stk.top();
    if (!info.first || (m - info.second) % info.first) return -1;
    i64 res = (m - info.second) / info.first;
    return res > 0 ? res : -1;
  }
 public:
  int findMissing(vector<int> s, int m) {
    int res = solve1(s, m);
    if (res != -1) return res;
    return solve2(s, m);
  }
};
