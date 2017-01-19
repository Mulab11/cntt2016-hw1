#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const i64 INF = 1LL << 60;

class SpaceWarDiv1 {
 public:
  i64 minimalFatigue(vector<int> s, vector<int> a, vector<i64> b) {
    i64 l = 1, r = INF;
    std::sort(s.begin(), s.end());
    while (l < r) { // binary search the answer
      i64 mid = (l + r) >> 1;
      std::vector< std::pair<int, i64> > cur;
      for (int i = 0; i < a.size(); ++i) cur.push_back(std::make_pair(a[i], b[i]));
      std::sort(cur.begin(), cur.end());
      for (int i = s.size() - 1; i >= 0; --i) {
        i64 x = mid;
        while (x && !cur.empty() && cur.back().first <= s[i]) {
          // greedily choose the enemy to defeat
          i64 y = std::min(cur.back().second, x);
          x -= y;
          if (!(cur.back().second -= y)) cur.pop_back();
        }
      }
      if (cur.empty()) r = mid; else l = mid + 1;
    }
    return l == INF ? -1 : l;
  }
};
