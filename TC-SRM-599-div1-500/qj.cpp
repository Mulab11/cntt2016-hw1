#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 10, M = 1 << 15;

class FindPolygons {
  short s[N * N];
  int x[M], y[M], z[M], tot;
 public:
  double minimumPolygon(int l) {
    if ((l & 1) || l == 2) return -1;
    // It's easy to prove that if l < 4, then the answer would also be -1.
    // If l >= 4, then we can easily construct an rectangle, which is the optimal quadrilateral.
    // Then we consider the triangles.
    memset(s, -1, sizeof s);
    tot = 0;
    for (int i = 0; i * i < N * N; ++i) s[i * i] = i;
    int res = l + 1;
    for (int i = 0; 2 * i <= l; ++i) {
      for (int j = !i; 2 * j <= l; ++j) {
        int k = s[i * i + j * j];
        if (k != -1) x[tot] = i, y[tot] = j, z[tot] = k, ++tot;
      }
    }
    // Here we enumerate all possible triples of edge lengths.
    for (int i = 0; i < tot; ++i) {
      for (int j = 0; j < i; ++j) {
        int a = x[i] - x[j], b = y[i] - y[j];
        if (a * a + b * b > N * N) continue;
        int c = s[a * a + b * b];
        if (c == -1 || x[i] * y[j] == y[i] * x[j]) continue;
        if (z[i] + z[j] + c == l) res = std::min(res, std::max(std::max(z[i], z[j]), c) - std::min(std::min(z[i], z[j]), c));
      }
    }
    if (res > l) res = (l % 4 ? 1 : 0);
    return res;
  }
};
