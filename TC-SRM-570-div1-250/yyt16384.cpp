#include <cstdlib>
#include <vector>

class RobotHerb {
  public:
    long long getdist(int T, std::vector<int> a);
};

long long RobotHerb::getdist(int T, std::vector<int> a)
{
    static const int DIRS[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int curdir = 0;
    int x = 0;
    int y = 0;
    for (auto p : a) {
        x += DIRS[curdir][0] * p;
        y += DIRS[curdir][1] * p;
        curdir = (curdir - p % 4 + 4) % 4;
    }
    if (curdir == 0) {
        // Move in the same direction T times
        return (long long)T * (std::abs(x) + std::abs(y));
    } else {
        // Move to the origin point after 4 times
        int sx = 0;
        int sy = 0;
        int dx = x;
        int dy = y;
        for (int i = 0; i < T % 4; i++) {
            sx += dx;
            sy += dy;
            int ndx = curdir == 2 ? -dx : (curdir == 1 ? -dy : dy);
            int ndy = curdir == 2 ? -dy : (curdir == 1 ? dx : -dx);
            dx = ndx;
            dy = ndy;
        }
        return std::abs(sx) + std::abs(sy);
    }
}
