#include <bits/stdc++.h>

using namespace std;

class UndoHistory {
  int lcp(const std::string &a, const std::string &b) {
    int res = 0;
    while (res < a.length() && res < b.length() && a[res] == b[res]) ++res;
    return res;
  }
 public:
  int minPresses(vector<string> a) {
    const int n = a.size();
    int res = n + a[0].length();
    for (int i = 1; i < n; ++i) {
      int cur = a[i].length() + 2; // minimum steps required
      for (int j = 0; j < i; ++j) cur = std::min<int>(cur, a[i].length() - lcp(a[i], a[j]) + 2); // use previous results
      if (lcp(a[i], a[i - 1]) == a[i - 1].length()) cur = std::min<int>(cur, a[i].length() - a[i - 1].length()); // don't need to undo
      res += cur;
    }
    return res;
  }
};
