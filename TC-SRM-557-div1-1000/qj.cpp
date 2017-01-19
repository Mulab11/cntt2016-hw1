#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class XorAndSum {
  std::vector<i64> b;
  void insert(i64 x) {
    for (int i = 0; i < b.size(); ++i) if ((x ^ b[i]) < x) x ^= b[i];
    if (x) b.push_back(x);
  }
 public:
  i64 maxSum(vector<i64> a) {
    const int n = a.size();
    for (int i = 0; i < n; ++i) insert(a[i]);
    std::sort(b.rbegin(), b.rend());
    for (int i = b.size() - 1; i >= 0; --i)
      for (int j = 0; j < i; ++j)
        if ((b[j] ^ b[i]) < b[j]) b[j] ^= b[i];
    // gaussian elimination
    i64 x = 0;
    for (int i = 0; i < b.size(); ++i) x ^= b[i];
    i64 res = x;
    for (int i = 1; i < b.size(); ++i) res += (x ^ b[i]); // greedy
    for (int i = n - b.size(); i--;) res += x;
    return res;
  }
};
