#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int S = 60;

class BitwiseAnd {
 public:
  vector<i64> lexSmallest(vector<i64> s, int n) {
    const int m = s.size();
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < i; ++j)
        if (!(s[i] & s[j])) return std::vector<i64>();
    std::vector<int> cnt(S);
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < S; ++j)
        if (s[i] >> j & 1) ++cnt[j];
    for (int i = 0; i < S; ++i) if (cnt[i] > 2) return std::vector<i64>();
    // First we construct a set S of which the size is n-m, such that each element in S is connected with elements in s.
    while (s.size() < n) {
      i64 t = 0;
      for (int i = 0; i < m; ++i) {
        bool flag = false;
        for (int j = 0; j < S; ++j) {
          if ((s[i] >> j & 1) && cnt[j] == 1) {
            t |= 1LL << j;
            ++cnt[j];
            flag = true;
            break;
          }
        }
        if (!flag) return std::vector<i64>();
      }
      s.push_back(t);
    }
    // Then we use the remaining bits to connect the elements in S.
    for (int i = m; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        bool flag = false;
        for (int k = 0; k < S; ++k) {
          if (cnt[k] == 0) {
            s[i] |= 1LL << k;
            s[j] |= 1LL << k;
            cnt[k] = 2;
            flag = true;
            break;
          }
        }
        if (!flag) return std::vector<i64>();
      }
    }
    std::sort(s.begin(), s.end());
    return s;
  }
};
