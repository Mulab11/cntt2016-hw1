#include <bits/stdc++.h>

using namespace std;

const int N = 2500 + 10;

class HexagonalBoard {
  int anc[N], col[N], size[N];
  int find(int x) {
    if (anc[x] == x) return x;
    int y = find(anc[x]);
    col[x] ^= col[anc[x]];
    return anc[x] = y;
  }
  bool meld(int x, int y) {
    int a = find(x), b = find(y);
    if (a == b) return col[x] != col[y];
    anc[a] = b;
    size[b] += size[a];
    col[a] ^= (col[x] == col[y]);
    return true;
  }
 public:
  int minColors(vector<string> s) {
    // the board can be easily 3-colored
    // so we only need to check if the answer can be 0, 1 or 2.
    const int dx[] = {-1, -1, 0, 0, 1, 1}, dy[] = {0, 1, -1, 1, -1, 0};
    const int n = s.size();
    for (int i = 0; i < n * n; ++i) anc[i] = i, size[i] = 1, col[i] = 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (s[i][j] == '-') continue;
        ++cnt;
        for (int k = 0; k < 6; ++k) {
          int x = i + dx[k], y = j + dy[k];
          if (0 <= x && x < n && 0 <= y && y < n && s[x][y] == 'X' && !meld(i * n + j, x * n + y)) return 3; // the board is not bipartite
        }
      }
    }
    for (int i = 0; i < n * n; ++i) if (size[find(i)] > 1) return 2;
    return cnt ? 1 : 0; // notice that the answer can be 0
  }
};
