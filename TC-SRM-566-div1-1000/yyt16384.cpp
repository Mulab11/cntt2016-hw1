#include <cmath>
#include <string>
#include <utility>
#include <vector>

const double PI = std::acos(-1);

class Point {
  public:
    double x = 0;
    double y = 0;

    Point() { }
    Point(double x_, double y_) : x(x_), y(y_) { }

    static double cross(const Point &x, const Point &y);
    static double cross(const Point &x, const Point &y, const Point &z);
};

Point operator+(const Point &x, const Point &y)
{
    return Point(x.x + y.x, x.y + y.y);
}

Point operator-(const Point &x, const Point &y)
{
    return Point(x.x - y.x, x.y - y.y);
}

double Point::cross(const Point &x, const Point &y)
{
    return x.x * y.y - x.y * y.x;
}

double Point::cross(const Point &x, const Point &y, const Point &z)
{
    return cross(y - x, z - x);
}

class FencingPenguins {
  public:
    int countWays(int numPosts, int radius, std::vector<int> x, std::vector<int> y, std::string color);

  private:
    static const int MOD = 100007;
};

int FencingPenguins::countWays(int numPosts, int radius, std::vector<int> x, std::vector<int> y, std::string color)
{
    int n = x.size();
    std::vector<std::pair<int, int>> checkpairs;
    for (int i = 0; i < n; i++) {
        bool ok = true;
        for (int j = 0; j < i; j++) {
            if (color[j] == color[i]) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }
        for (int j = i + 1; j < n; j++) {
            if (color[j] == color[i]) {
                checkpairs.push_back(std::make_pair(i, j));
            }
        }
    }
    std::vector<Point> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = Point(x[i], y[i]);
    }
    std::vector<Point> a(numPosts);
    for (int i = 0; i < numPosts; i++) {
        double angle = 2 * PI * i / numPosts;
        a[i] = Point(std::cos(angle) * radius, std::sin(angle) * radius);
    }
    // insidemask[i][j] = set of points that lies on the left of (a[i],
    // a[j])
    std::vector<std::vector<long long>> insidemask(numPosts, std::vector<long long>(numPosts));
    for (int i = 0; i < numPosts; i++) {
        for (int j = 0; j < numPosts; j++) {
            if (i != j) {
                for (int k = 0; k < n; k++) {
                    if (Point::cross(c[k], a[i], a[j]) > 0) {
                        insidemask[i][j] |= 1LL << k;
                    }
                }
            }
        }
    }
    for (int i = 0; i < numPosts; i++) {
        if (insidemask[(i + 1) % numPosts][i]) {
            // Penguin is outside of the boundary polygon
            return 0;
        }
    }
    // segok[i][j] = whether segment (a[i], a[j]) can be chosen without
    // splitting penguins of the same color into two parts
    std::vector<std::vector<char>> segok(numPosts, std::vector<char>(numPosts));
    for (int i = 0; i < numPosts; i++) {
        for (int j = i + 1; j < numPosts; j++) {
            bool ok = true;
            for (auto p : checkpairs) {
                if (((insidemask[i][j] >> p.first) & 1) != ((insidemask[i][j] >> p.second) & 1)) {
                    ok = false;
                    break;
                }
            }
            segok[i][j] = ok;
        }
    }
    // rangeok[i][j] = whether there are no penguins inside polygon
    // (a[i-1], a[i], a[j], a[j+1])
    std::vector<std::vector<char>> rangeok(numPosts, std::vector<char>(numPosts));
    for (int i = 0; i < numPosts; i++) {
        for (int j = i; j < numPosts; j++) {
            if (i == 0 && j == numPosts - 1) {
                rangeok[i][j] = true;
                continue;
            }
            int prev = (i + numPosts - 1) % numPosts;
            int next = (j + 1) % numPosts;
            long long s = ~insidemask[prev][next] & ~insidemask[j][i] & ((1LL << n) - 1);
            rangeok[i][j] = s == 0;
        }
    }
    // f[i][j] = number of ways to create polygons with a[i..j] to
    // enclose all penguins inside the range
    std::vector<std::vector<int>> f(numPosts, std::vector<int>(numPosts));
    // g[i][j][k] = number of ways to have i as the starting vertex, j
    // as the current vertex and whether current polygon already
    // contains a penguin == k
    std::vector<std::vector<std::pair<int, int>>> g(numPosts, std::vector<std::pair<int, int>>(numPosts));
    for (int i = numPosts - 1; i >= 0; i--) {
        g[i][i].first = 1;
        for (int j = i; j < numPosts; j++) {
            for (int k = j + 1; k < numPosts; k++) {
                if (!segok[j][k]) {
                    continue;
                }
                int w = (long long)g[i][j].first * (j + 1 == k ? 1 : f[j + 1][k - 1]) % MOD;
                if (insidemask[i][j] & insidemask[j][k] & insidemask[k][i]) {
                    g[i][k].second = (g[i][k].second + w) % MOD;
                } else {
                    g[i][k].first = (g[i][k].first + w) % MOD;
                }
                g[i][k].second = (g[i][k].second + (long long)g[i][j].second * (j + 1 == k ? 1 : f[j + 1][k - 1])) % MOD;
            }
        }
        std::vector<int> h(numPosts);
        for (int j = i; j < numPosts; j++) {
            for (int k = i; k < j; k++) {
                if (!segok[k][j]) {
                    continue;
                }
                if (!(insidemask[i][k] & insidemask[k][j] & insidemask[j][i]) && !insidemask[k][i]) {
                    h[j] = (h[j] + (long long)g[k][j].second) % MOD;
                }
            }
            if (!rangeok[i][j]) {
                continue;
            }
            if (!insidemask[j][i]) {
                // No penguins in this range
                f[i][j] = 1;
                continue;
            }
            for (int k = i + 1; k <= j; k++) {
                if (!(insidemask[i][k] & insidemask[k][j] & insidemask[j][i])) {
                    f[i][j] = (f[i][j] + (long long)h[k] * (k == j ? 1 : f[k + 1][j])) % MOD;
                }
            }
        }
    }
    return f[0][numPosts - 1];
}
