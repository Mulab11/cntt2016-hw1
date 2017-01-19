#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 2000000 + 10, MOD = 1000000007;

class WolfDelaymasterHard {
  int f[N], pw[N], po[N], so[N], sw[N];
 public:
  int countWords(int n, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd) {
    std::string s(n, '?');
    i64 x = w0;
    for(int i = 0; i < wlen; ++i) {
      s[x] = 'w';
      x = (x * wmul + wadd) % n;
    }
    x = o0;
    for(int i = 0; i < olen; ++i) {
      s[x] = 'o';
      x = (x * omul + oadd) % n;
    }
    // po is the position of previous 'o', so is the position of next 'o'
    // pw is the position of previous 'w', sw is the position of next 'w'
    for (int i = 0; i <= n; ++i) {
      if (i) po[i] = po[i - 1], pw[i] = pw[i - 1]; else po[i] = pw[i] = -1;
      if (s[i] == 'o') po[i] = i;
      if (s[i] == 'w') pw[i] = i;
    }
    so[n] = sw[n] = n;
    for (int i = n - 1; i >= 0; --i) {
      so[i] = so[i + 1], sw[i] = sw[i + 1];
      if (s[i] == 'o') so[i] = i;
      if (s[i] == 'w') sw[i] = i;
    }
    memset(f, 0, sizeof f);
    f[0] = 1;
    f[1] = -1;
    // f[i]: number of ways to make prefix s[0, i) legal
    for (int i = 0; i < n; (f[i + 2] += ((f[i + 1] += f[i]) %= MOD)) %= MOD, i += 2) {
      if (po[i] == i) continue;
      for (int l = 1; i + 2 * l <= n;) {
        if (po[i + l - 1] >= i) break;
        if (pw[i + 2 * l - 1] >= i + l) {
          l = pw[i + 2 * l - 1] - i + 1;
          continue;
        }
        int r = std::min((sw[i + 2 * l] - i) / 2, so[i] - i); // get the rightmost position
        // f[i] can be used to update f[i + 2 * j], where l <= j <= r
        (f[i + 2 * l] += f[i]) %= MOD; // add a tag
        (f[i + 2 * r + 1] -= f[i]) %= MOD; // add a tag
        l = r + 1;
        // there will be at most O(log n) intervals, so we could use brute force to find all intervals.
      }
    }
    return (f[n] + MOD) % MOD;
  }
};
