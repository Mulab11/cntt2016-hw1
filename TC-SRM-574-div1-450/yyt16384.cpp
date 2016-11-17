#include <vector>

class PolygonTraversal {
  public:
    long long count(int N, std::vector<int> points);
};

long long PolygonTraversal::count(int N, std::vector<int> points)
{
    // Whether there are any intersections only depends on which points
    // are already chosen
    // f[i][j] = number of ways starting from the state where set i is
    // chosen and current point is j
    std::vector<std::vector<long long>> f(1 << N, std::vector<long long>(N));
    for (int i = 0; i < N; i++) {
        if (i != (points[0] + N - 2) % N && i != points[0] % N) {
            f[(1 << N) - 1][i] = 1;
        }
    }
    for (int i = (1 << N) - 2; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            if ((i >> j) & 1) {
                int next = (j + 1) % N;
                while (!((i >> next) & 1)) {
                    next = (next + 1) % N;
                }
                int prev = (j + N - 1) % N;
                while (!((i >> prev) & 1)) {
                    prev = (prev + N - 1) % N;
                }
                for (int k = next; k != prev; k = (k + 1) % N) {
                    if (!((i >> k) & 1)) {
                        f[i][j] += f[i | (1 << k)][k];
                    }
                }
            }
        }
    }
    int s = 0;
    for (auto x : points) {
        s |= 1 << (x - 1);
    }
    return f[s][points.back() - 1];
}
