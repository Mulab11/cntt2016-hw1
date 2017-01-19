#include <bits/stdc++.h>

using namespace std;

class TheNumberGame {
  std::string convert(int a) {
    std::stringstream ss;
    ss << a;
    return ss.str();
  }
 public:
  string determineOutcome(int _a, int _b) {
    // the strategy is to keep that b is always a substring of a (or rev(a))
    std::string a = convert(_a), b = convert(_b), c = b;
    std::reverse(c.begin(), c.end());
    return (a.find(b) != std::string::npos || a.find(c) != std::string::npos) ? "Manao wins" : "Manao loses";
  }
};
