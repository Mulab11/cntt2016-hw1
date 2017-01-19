#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 2000000 + 10, MOD = 1000000007;

class LittleElephantAndBoard {
  int power(int base, int exp) {
    int res = 1;
    for (; exp; exp >>= 1) {
      if (exp & 1) res = (i64)res * base % MOD;
      base = (i64)base * base % MOD;
    }
    return res;
  }
  int fact[N], inv[N];
  int binom(int n, int m) { // binomial coefficients
    if (m < 0 || m > n) return 0;
    return (i64)fact[n] * inv[m] % MOD * inv[n - m] % MOD;
  }
  int calc(int n, int m, int a, int b) {
    // There are n segments, a color A, b color B.
    if (n <= 0) return 0;
    if (a > b) std::swap(a, b);
    int res = 0;
    for (int i = b - a; i <= n; i += 2) {
      // Enumerate the number of segments of which the length is an odd number.
      int x = (i - (b - a)) / 2;
      int y = m - i - 2 * (n - i);
      // Calculate the number of segments that are ABAB...A and number of BABA...B
      if (y >= 0 && !(y & 1)) {
        y /= 2;
        res = (res + (i64)binom(n, i) * binom(i, x) % MOD * power(2, n - i) % MOD * binom(y + n - 1, y)) % MOD;
      }
    }
    return res;
  }
 public:
  int getNumber(int m, int r, int g, int b) {
    // Use the missing color in each column to form a new array.
    fact[0] = 1;
    for (int i = 1; i < N; ++i) fact[i] = (i64)fact[i - 1] * i % MOD;
    inv[N - 1] = power(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; --i) inv[i] = inv[i + 1] * (i + 1LL) % MOD;
    r = m - r, g = m - g, b = m - b;
    // Number of segments could only be r-1, r or r+1.
    int ans = calc(r + 1, m - r, g, b);
    ans = (ans + 2LL * calc(r, m - r, g, b)) % MOD;
    ans = (ans + calc(r - 1, m - r, g, b)) % MOD;
    ans = 2LL * ans % MOD; // One new array maps to two origin matrix.
    return ans;
  }
};
