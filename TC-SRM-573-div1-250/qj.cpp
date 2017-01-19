#include <bits/stdc++.h>

using namespace std;

class TeamContest {
  inline int calc(int a, int b, int c) { return std::max(std::max(a, b), c) + std::min(std::min(a, b), c); } // calculate the strength of the team
 public:
  int worstRank(vector<int> a) {
    int cur = calc(a[0], a[1], a[2]);
    std::sort(a.begin() + 3, a.end());
    int res = 1;
    for (int i = a.size() - 1, j = 3; i >= j; --i) {
      // greedy
      while (i - j > 1 && a[j] + a[i] <= cur) ++j;
      if (i - j > 1) ++res, j += 2; else break;
    }
    return res;
  }
};
