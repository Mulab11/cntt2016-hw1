#include <bits/stdc++.h>

using namespace std;

class KingdomAndDice {
  static const int N = 50 + 10;
  std::bitset<N * N> f[N];
 public:
  double newFairness(vector<int> a, vector<int> b, int x) {
    const int n = a.size();
    std::sort(a.begin(), a.end());
    int m = 0;
    while (m < n && !a[m]) ++m;
    std::sort(b.begin(), b.end());
    std::set<int> pool(b.begin(), b.end());
    for (int i = m; i < n; ++i) pool.insert(a[i]);
    std::vector<int> cur;
    for (int i = 0; i < b.size(); ++i)
      for (int j = std::max(b[i] - m, 1); j <= b[i] + m && j <= x; ++j)
        if (!pool.count(j)) cur.push_back(j);
    std::sort(cur.begin(), cur.end());
    cur.erase(std::unique(cur.begin(), cur.end()), cur.end());
    int res = 0;
    for (int i = m; i < n; ++i) res += std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    f[0][res] = 1;
    // knapsack
    for (int i = 0; i < cur.size(); ++i) {
      int temp = std::lower_bound(b.begin(), b.end(), cur[i]) - b.begin();
      for (int j = m; j > 0; --j) f[j] |= f[j - 1] << temp;
    }
    for (int j = 1; j <= m; ++j) f[j] |= f[j - 1];
    for (int j = 0; j <= n * n; ++j) if (f[m][j] && abs(2 * j - n * n) < abs(2 * res - n * n)) res = j;
    return (double)res / n / n;
  }
};
