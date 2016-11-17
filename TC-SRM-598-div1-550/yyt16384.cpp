#include <string>

class FoxAndFencing {
  public:
    std::string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d);
};

std::string FoxAndFencing::WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d)
{
    if (mov1 + rng1 >= d) {
        return "Ciel";  // Ciel wins in the first turn
    }
    if (mov2 + rng2 >= d + mov1) {
        return "Liss";  // Liss wins in the second turn
    }
    // Otherwise, the player with larger move length can always escape,
    // and she need to attack while staying outside of the other
    // player's possible attack range
    if (mov1 > mov2 && mov1 + rng1 >= mov2 + rng2 + 1 + mov2) {
        return "Ciel";
    }
    if (mov2 > mov1 && mov2 + rng2 >= mov1 + rng1 + 1 + mov1) {
        return "Liss";
    }
    return "Draw";
}
