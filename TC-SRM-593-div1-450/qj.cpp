#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 1, M = 1000000 + 10;

class MayTheBestPetWin {
  std::bitset<M> mask;
 public:
  int calc(vector<int> a, vector<int> b) {
    // let A = \sum a_i, B = \sum b_i
    // let a = the sum of a_i in the first set, b = the sum of b_i in the first set
    // then our goal is to minimize max(a + b - A, B - (a + b))
    // since the answer is only related to a + b, we can solve it by DP
    mask[0] = 1;
    const int n = a.size();
    int x = 0, y = 0;
    for (int i = 0; i < n; ++i) mask |= mask << (a[i] + b[i]); // calculate all possible a + b
    for (int i = 0; i < n; ++i) x += a[i], y += b[i];
    int ans = x + y;
    for (int i = 0; i < M; ++i) if (mask[i]) ans = std::min(ans, std::max(i - x, y - i)); // calculate the answer
    return ans;
  }
};
