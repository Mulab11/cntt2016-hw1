#include <bits/stdc++.h>

using namespace std;

class NewArenaPassword {
  static const int N = 50 + 10;
  int anc[N];
  int find(int x) { return anc[x] == x ? x : (anc[x] = find(anc[x])); }
 public:
  int minChange(string s, int k) {
    const int n = s.length();
    for (int i = 0; i < n; ++i) anc[i] = i;
    for (int i = 0; i < k; ++i) anc[find(i)] = find(s.length() - k + i);
    int res = 0;
    std::vector<bool> flag(n);
    for (int i = 0; i < k; ++i) {
      if (flag[find(i)]) continue;
      flag[find(i)] = true;
      std::vector<int> cnt(26);
      for (int j = 0; j < n; ++j) if (find(j) == find(i)) ++cnt[s[j] - 'a']; // count the number of the j-th char
      res += std::accumulate(cnt.begin(), cnt.end(), -*std::max_element(cnt.begin(), cnt.end())); // sum - max
    }
    return res;
  }
};
