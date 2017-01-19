#include <bits/stdc++.h>

using namespace std;

class LittleElephantAndString {
  bool check(std::string a, std::string b) {
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    return a == b;
  }
 public:
  int getNumber(string a, string b) {
    // The problem is equivalent to calculate the length of the longest subsequence of a, which is a suffix of b.
    if (!check(a, b)) return -1;
    int j = b.length() - 1;
    for (int i = a.length() - 1; i >= 0; --i) if (j >= 0 && a[i] == b[j]) --j;
    return j + 1;
  }
};
