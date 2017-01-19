#include <bits/stdc++.h>

using namespace std;

class FoxAndHandle {
  static const int S = 26;
 public:
  string lexSmallestName(string s) {
    std::vector<int> cnt(S);
    const int n = s.length();
    for (int i = 0; i < n; ++i) ++cnt[s[i] - 'a'];
    for (int i = 0; i < S; ++i) cnt[i] /= 2;
    std::string res;
    for (int i = n / 2; i--;) {
      for (int j = 0; j < S; ++j) {
        // greedy
        if (!cnt[j]) continue;
        --cnt[j];
        res += j + 'a';
        int p = 0, q = 0;
        for (; q < n && p < res.length(); ++q) if (s[q] == res[p]) ++p;
        std::vector<int> cur(S);
        for (; q < n; ++q) ++cur[s[q] - 'a'];
        for (int k = 0; k < S; ++k) if (cur[k] < cnt[k]) goto fail;
        break;
     fail:
        res.pop_back();
        ++cnt[j];
      }
    }
    return res;
  }
};
