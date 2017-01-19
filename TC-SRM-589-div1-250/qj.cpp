#include <bits/stdc++.h>

using namespace std;

const int N = 26;

class GooseTattarrattatDiv1 {
  int anc[N], mx[N];
  int find(int x) { return anc[x] == x ? x : (anc[x] = find(anc[x])); }
  void meld(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    anc[x] = y;
    mx[y] = std::max(mx[y], mx[x]);
  }
 public:
  int getmin(string s) {
    memset(mx, 0, sizeof mx);
    for (int i = 0; i < N; ++i) anc[i] = i;
    for (int i = 0; i < s.length(); ++i) ++mx[s[i] - 'a'];
    for (int i = 0, j = s.length() - 1; i < j; ++i, --j) meld(s[i] - 'a', s[j] - 'a'); // these characters must be same
    int res = s.length();
    for (int i = 0; i < N; ++i) if (find(i) == i) res -= mx[i]; // the minimal cost of a connected component is min cnt_i
    return res;
  }
};
