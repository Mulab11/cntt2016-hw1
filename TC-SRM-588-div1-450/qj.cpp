#include <bits/stdc++.h>

using namespace std;

const int N = 12, M = 133;

class KeyDungeonDiv1 {
  int f[1 << N][M];
  inline void check(int &lhs, int rhs) { if (rhs > lhs) lhs = rhs; }
 public:
  int maxKeys(vector<int> doorR, vector<int> doorG, vector<int> roomR, vector<int> roomG, vector<int> roomW, vector<int> keys) {
    const int n = doorR.size();
    memset(f, -1, sizeof f);
    f[0][keys[0]] = keys[2]; // f[s][i]: we have opened all doors in s, number of the red keys we have is i, the maximal possible number of white keys we have is f[s][i]
    int res = 0;
    for (int s = 0; s < (1 << n); ++s) {
      for (int a = 0; a < M; ++a) {
        int c = f[s][a];
        if (c == -1) continue;
        int b = keys[0] + keys[1] + keys[2];
        for (int j = 0; j < n; ++j) if (s >> j & 1) b += roomR[j] + roomG[j] + roomW[j] - doorR[j] - doorG[j];
        check(res, b);
        b -= a + c;
        // calculate the numbers of each type of keys we have
        for (int j = 0; j < n; ++j) {
          if (s >> j & 1) continue;
          int x = a - doorR[j], y = b - doorG[j], z = c;
          if (x < 0) z += x, x = 0;
          if (y < 0) z += y, y = 0;
          if (z < 0) continue;
          x += roomR[j], y += roomG[j], z += roomW[j];
          check(f[s | (1 << j)][x], z);
        }
      }
    }
    return res;
  }
};
