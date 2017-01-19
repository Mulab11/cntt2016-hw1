#include <bits/stdc++.h>

using namespace std;

class FoxAndChess {
 public:
  string ableToMove(string a, string b) {
    std::vector< std::pair<int, char> > p, q;
    for (int i = 0; i < a.length(); ++i) if (a[i] != '.') p.push_back(std::make_pair(i, a[i]));
    for (int i = 0; i < b.length(); ++i) if (b[i] != '.') q.push_back(std::make_pair(i, b[i]));
    if (p.size() != q.size()) return "Impossible"; // the number of pawns must be equal
    for (int i = 0; i < p.size(); ++i) {
      if (p[i].second != q[i].second) return "Impossible"; // the type of the pawn must be equal
      if (p[i].second == 'L' && p[i].first < q[i].first) return "Impossible"; // L could only move to the left
      if (p[i].second == 'R' && p[i].first > q[i].first) return "Impossible"; // R could only move to the right
    }
    return "Possible";
  }
};
