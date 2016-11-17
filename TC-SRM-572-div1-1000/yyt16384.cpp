#include <algorithm>
#include <array>
#include <string>

static const int INF = 0x3f3f3f3f;

class NextAndPrev {
  public:
    int getMinimum(int nextCost, int prevCost, std::string start, std::string goal);

  private:
    static const int SZ = 26;

    int getMinimum2(const std::array<int, SZ> &a, int nextCost, int prevCost);
};

int NextAndPrev::getMinimum(int nextCost, int prevCost, std::string start, std::string goal)
{
    std::array<int, SZ> a;
    a.fill(-INF);
    for (int i = 0; i < (int)start.length(); i++) {
        int x = start[i] - 'a';
        int y = goal[i] - 'a';
        if (a[x] != -INF && a[x] != y) {
            return -1;
        }
        a[x] = y;
    }
    bool fl = true;
    for (int i = 0; i < SZ; i++) {
        if (a[i] == -INF || (a[i] - i + SZ) % SZ != a[0]) {
            fl = false;
            break;
        }
    }
    if (fl && a[0] != 0) {
        // Special case
        return -1;
    }
    int ans = INF;
    for (int i = 0; i < SZ; i++) {
        std::array<int, SZ> b;
        // Shift letters by i
        for (int j = 0; j < SZ; j++) {
            b[(j + i) % SZ] = a[j] == -INF ? -INF : a[j] + i;
        }
        ans = std::min(ans, getMinimum2(b, nextCost, prevCost));
        std::array<int, SZ> c;
        for (int j = 0; j < SZ; j++) {
            c[j] = b[j] == -INF ? -INF : b[j] + SZ;
        }
        ans = std::min(ans, getMinimum2(c, nextCost, prevCost));
        std::array<int, SZ> d;
        for (int j = 0; j < SZ; j++) {
            d[j] = b[j] == -INF ? -INF : b[j] - SZ;
        }
        ans = std::min(ans, getMinimum2(d, nextCost, prevCost));
    }
    return ans == INF ? -1 : ans;
}

int NextAndPrev::getMinimum2(const std::array<int, SZ> &a, int nextCost, int prevCost)
{
    int last = -INF;
    int pre = -1;
    int ans = 0;
    for (int i = 0; i < SZ; i++) {
        if (a[i] != -INF) {
            if (a[i] < last) {
                // Movements cannot intersect
                return INF;
            }
            if (a[i] > last) {
                if (i <= a[i]) {
                    ans += (a[i] - i) * nextCost;
                }
                if (pre != -1 && pre > last) {
                    ans += (pre - last) * prevCost;
                }
            }
            last = a[i];
            pre = i;
        }
    }
    if (pre != -1 && pre > last) {
        ans += (pre - last) * prevCost;
    }
    return ans;
}
