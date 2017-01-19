#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class CuttingBitString {
  static const int N = 50 + 10, INF = 0x3f3f3f3f;
 public:
  int getmin(string s) {
    i64 t = 1;
    std::string pat[30];
    for (int i = 0; i < 25; ++i, t *= 5) {
      pat[i] = std::bitset<64>(t).to_string();
      std::reverse(pat[i].begin(), pat[i].end());
      while (pat[i].back() == '0') pat[i].pop_back();
      std::reverse(pat[i].begin(), pat[i].end());
    }
    int f[N];
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    const int n = s.length();
    for (int i = 0; i < n; ++i)
      for (int j = 0, k; j < 25 && (k = i + pat[j].length()) <= n; ++j)
        if (s.substr(i, pat[j].length()) == pat[j]) f[k] = std::min(f[k], f[i] + 1);
    return f[n] == INF ? -1 : f[n];
  }
};
