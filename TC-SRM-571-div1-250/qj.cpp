#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class FoxAndMp3 {
 public:
  vector<string> playList(int n) {
    std::vector<std::string> res;
    for (i64 i = 1; i <= n; i *= 10) {
      for (int j = 0; j <= 50 && i + j <= n && i + j < 10 * i; ++j) {
        // only these file names are possible
        std::stringstream ss;
        ss << i + j << ".mp3";
        res.push_back(ss.str());
      }
    }
    std::sort(res.begin(), res.end());
    if (res.size() > 50) res.resize(50);
    return res;
  }
};
