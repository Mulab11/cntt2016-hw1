#include <algorithm>

class TheBrickTowerEasyDivOne {
  public:
    int find(int redCount, int redHeight, int blueCount, int blueHeight);
};

int TheBrickTowerEasyDivOne::find(int redCount, int redHeight, int blueCount, int blueHeight)
{
    // The difference between the number of red and blue bricks should
    // be <= 1
    return std::min(redCount, blueCount) * (2 + (redHeight != blueHeight)) + (redCount != blueCount);
}
