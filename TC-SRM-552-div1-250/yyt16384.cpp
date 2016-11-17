#include <algorithm>

class FoxPaintingBalls {
  public:
    long long theMax(long long R, long long G, long long B, int N);
};

long long FoxPaintingBalls::theMax(long long R, long long G, long long B, int N)
{
    long long s = (long long)N * (N + 1) / 2;
    long long p = s / 3;
    if (N % 3 != 1) {
        // In every possible coloring, red count = green count = blue
        // count
        return std::min({R / p, G / p, B / p});
    } else if (N > 1) {
        // For each ball triangle one extra ball can be colored with any
        // color
        return std::min({R / p, G / p, B / p, (R + G + B) / s});
    } else {
        // Avoid division by zero when p = 0
        return R + G + B;
    }
}
