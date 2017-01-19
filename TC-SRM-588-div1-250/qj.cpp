#include <bits/stdc++.h>

using namespace std;

class GUMIAndSongsDiv1 {
 public:
  int maxSongs(vector<int> d, vector<int> t, int m) {
    std::vector< std::pair<int, int> > pool;
    const int n = d.size();
    for (int i = 0; i < n; ++i) pool.push_back(std::make_pair(t[i], d[i]));
    std::sort(pool.begin(), pool.end()); // sort all songs by t_i
    int res = 0;
    for (int i = 0; i < n; ++i) {
      std::multiset<int> cur;
      for (int j = i; j < n; ++j) {
        // enumerate the range of tones of the songs we sing
        cur.insert(pool[j].second);
        int temp = m - (pool[j].first - pool[i].first), cnt = 0;
        for (std::multiset<int>::iterator it = cur.begin(); it != cur.end(); ++it) if ((temp -= *it) >= 0) ++cnt; else break;
        res = std::max(res, cnt);
      }
    }
    return res;
  }
};
