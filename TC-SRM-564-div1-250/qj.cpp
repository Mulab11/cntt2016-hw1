#include <bits/stdc++.h>

using namespace std;

class KnightCircuit2 {
 public:
  int maxSize(int w, int h) {
    // every 3 * 4 submatrix is connected
    if (std::min(w, h) == 1) return 1;
    if (std::min(w, h) == 2) return (std::max(w, h) + 1) / 2;
    if (w == 3 && w == h) return 8;
    return w * h;
  }
};
