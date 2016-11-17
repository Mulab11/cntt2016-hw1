#include <algorithm>
#include <array>

class HyperKnight {
  public:
    long long countCells(int a, int b, int numRows, int numColumns, int k);
};

long long HyperKnight::countCells(int a, int b, int numRows, int numColumns, int k)
{
    std::array<int, 8> dlx = {a, b, a, b, 0, 0, 0, 0};
    std::array<int, 8> drx = {0, 0, 0, 0, a, b, a, b};
    std::array<int, 8> dly = {b, a, 0, 0, 0, 0, b, a};
    std::array<int, 8> dry = {0, 0, b, a, b, a, 0, 0};
    std::array<long long, 256> f = {0};
    long long ans = 0;
    // Enumerate the set of allowed moves
    for (int i = (1 << 8) - 1; i >= 0; i--) {
        int cnt = 0;
        int dlxs = 0;
        int drxs = 0;
        int dlys = 0;
        int drys = 0;
        for (int j = 0; j < 8; j++) {
            if ((i >> j) & 1) {
                cnt++;
                dlxs = std::max(dlxs, dlx[j]);
                drxs = std::max(drxs, drx[j]);
                dlys = std::max(dlys, dly[j]);
                drys = std::max(drys, dry[j]);
            }
        }
        int xcnt = std::max(numRows - dlxs - drxs, 0);
        int ycnt = std::max(numColumns - dlys - drys, 0);
        f[i] = (long long)xcnt * ycnt;
        for (int j = i + 1; j < (1 << 8); j++) {
            if ((i & j) == i) {
                f[i] -= f[j];
            }
        }
        if (cnt == k) {
            ans += f[i];
        }
    }
    return ans;
}
