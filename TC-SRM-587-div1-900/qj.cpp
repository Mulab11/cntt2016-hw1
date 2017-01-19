#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 10;

class ThreeColorability {
  int n, m;
  int anc[N];
  bool col[N];
  int find(int x) {
    if (anc[x] == x) return x;
    int y = find(anc[x]);
    col[x] ^= col[anc[x]];
    return anc[x] = y;
  }
  bool meld(int x, int y, bool z) {
    // z is true: x != y
    // z is false: x == y
    // this dsu is used to detect whether the graph is bipartite
    int a = find(x), b = find(y);
    if (a == b) return (col[x] != col[y]) == z;
    anc[a] = b;
    col[a] ^= ((col[x] != col[y]) != z);
    return true;
  }
 public:
  vector<string> lexSmallest(vector<string> res) {
    n = res.size(), m = res[0].length();
    for (int i = 0; i < n + m; ++i) col[anc[i] = i] = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        // check if illegal and link the edges
        if (res[i][j] == 'N' && !meld(i, j + n, 0)) return std::vector<std::string>();
        if (res[i][j] == 'Z' && !meld(i, j + n, 1)) return std::vector<std::string>();
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        // greedy
        if (res[i][j] == '?') {
          if (find(i) != find(j + n)) meld(i, j + n, 0);
          find(i), find(j + n);
          res[i][j] = (col[i] == col[j + n] ? 'N' : 'Z');
        }
      }
    }
    return res;
  }
};
