#include <bits/stdc++.h>

#define fst first
#define snd second

using namespace std;

typedef std::pair<int, int> Info;

class NextAndPrev {
  static const int INF = 1 << 27;
 public:
  int getMinimum(int a, int b, string s, string e) {
    if (s == e) return 0;
    const int n = 26;
    std::vector<int> to(n, -1);
    for (int i = 0; i < s.length(); ++i) {
      int &cur = to[s[i] - 'a'];
      if (cur == -1) cur = e[i] - 'a';
      if (cur != e[i] - 'a') return -1;
    }
    int mask = 0;
    for (int i = 0; i < e.length(); ++i) mask |= 1 << (e[i] - 'a');
    if (__builtin_popcount(mask) == n) return -1;
    std::vector<Info> info;
    for (int i = 0; i < n; ++i) if (to[i] != -1) info.push_back(std::make_pair(i, to[i]));
    int res = INF;
    for (int cnt = n; cnt--;) {
      // enumerate the separator
      for (int j = 1; j < info.size(); ++j) if (info[j].snd < info[j - 1].snd) goto fail;
      for (int t = -2; t <= 2; ++t) {
        // enumerate the rounds
        int cur = 0;
        for (int j = 0; j < info.size();) {
          int k = j;
          while (k < info.size() && info[k].snd == info[j].snd) ++k;
          int l = info[j].fst, r = info[k - 1].fst, p = info[j].snd + t * n;
          cur += std::max(p - l, 0) * a;
          cur += std::max(r - p, 0) * b;
          j = k;
        }
        res = std::min(res, cur);
      }
   fail:
      info[0].fst += n;
      std::rotate(info.begin(), info.begin() + 1, info.end());
    }
    return res == INF ? -1 : res;
  }
};
