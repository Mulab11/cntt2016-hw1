#include <bits/stdc++.h>

using namespace std;

class FoxAndFencing {
 public:
  string WhoCanWin(int a1, int a2, int b1, int b2, int d) {
    // First check if the game could end in just 1 turn,
    if (a1 + b1 >= d) return "Ciel";
    if (a2 + b2 >= a1 + d) return "Liss";
    // then check if one could catch up with the other.
    if (a1 > a2) {
      if (a1 + b1 > 2 * a2 + b2) return "Ciel"; else return "Draw";
    } else if (a1 == a2) {
      return "Draw";
    } else {
      if (a2 + b2 > 2 * a1 + b1) return "Liss"; else return "Draw";
    }
  }
};
