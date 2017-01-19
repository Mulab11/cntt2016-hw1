#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class TheNumberGameDivOne {
 public:
  string find(i64 n) {
    if (n & 1) return "Brus";
    return (__builtin_popcountll(n) == 1 && !(__builtin_clzll(n) & 1)) ? "Brus" : "John"; // find the pattern
  }
};
