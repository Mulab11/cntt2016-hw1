#include <utility>

class KnightCircuit2 {
  public:
    int maxSize(int w, int h);
};

int KnightCircuit2::maxSize(int w, int h)
{
    if (w > h) {
        std::swap(w, h);
    }
    if (w == 1) {
        // No moves possible
        return 1;
    } else if (w == 2) {
        // Can only move up or down in each cell
        return (h + 1) / 2;
    } else {
        // All cells reachable for 3x4 board
        return w * h - (w == 3 && h == 3);
    }
}
