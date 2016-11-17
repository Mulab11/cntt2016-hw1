#include <algorithm>
#include <utility>
#include <vector>

class Point {
  public:
    int x = 0;
    int y = 0;

    Point() { }
    Point(int x_, int y_) : x(x_), y(y_) { }

    static int cross(const Point &x, const Point &y);
    static int cross(const Point &x, const Point &y, const Point &z);
    static int dot(const Point &x, const Point &y);
    static int dot(const Point &x, const Point &y, const Point &z);
};

Point operator+(const Point &x, const Point &y)
{
    return Point(x.x + y.x, x.y + y.y);
}

Point operator-(const Point &x, const Point &y)
{
    return Point(x.x - y.x, x.y - y.y);
}

bool operator==(const Point &x, const Point &y)
{
    return x.x == y.x && x.y == y.y;
}

bool operator!=(const Point &x, const Point &y)
{
    return !(x == y);
}

int Point::cross(const Point &x, const Point &y)
{
    return x.x * y.y - x.y * y.x;
}

int Point::cross(const Point &x, const Point &y, const Point &z)
{
    return cross(y - x, z - x);
}

int Point::dot(const Point &x, const Point &y)
{
    return x.x * y.x + x.y * y.y;
}

int Point::dot(const Point &x, const Point &y, const Point &z)
{
    return dot(y - x, z - x);
}

class Constellation {
  public:
    double expectation(std::vector<int> X, std::vector<int> Y, std::vector<int> prob);

  private:
    double expectation2(std::vector<std::pair<Point, double>> a);
};

double Constellation::expectation(std::vector<int> X, std::vector<int> Y, std::vector<int> prob)
{
    int n = X.size();
    std::vector<std::pair<Point, double>> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = std::make_pair(Point(X[i], Y[i]), prob[i] / 1000.0);
    }
    double ans = 0;
    // Enumerate the bottom-left point
    for (auto x : a) {
        double p = 1;
        std::vector<std::pair<Point, double>> b = {std::make_pair(Point(), x.second)};
        for (auto y : a) {
            if (y.first.y < x.first.y || (y.first.y == x.first.y && y.first.x < x.first.x)) {
                // This point cannot be chosen
                p *= 1 - y.second;
            } else if (y.first != x.first) {
                b.push_back(std::make_pair(y.first - x.first, y.second));
            }
        }
        auto cmp = [](const std::pair<Point, double> &u, const std::pair<Point, double> &v) {
            int d = Point::cross(u.first, v.first);
            return d > 0 || (d == 0 && Point::dot(u.first, v.first - u.first) < 0);
        };
        std::sort(b.begin() + 1, b.end(), cmp);
        ans += p * expectation2(b);
    }
    return ans;
}

double Constellation::expectation2(std::vector<std::pair<Point, double>> a)
{
    a.push_back(a[0]);
    int n = a.size();
    // f[i][j] = probability of having an i -> j edge
    // g[i][j] = expected sum of cross products when having an i -> edge
    std::vector<std::vector<double>> f(n, std::vector<double>(n));
    std::vector<std::vector<double>> g(n, std::vector<double>(n));
    for (int i = 1; i < n; i++) {
        double t = a[i].second;
        for (int j = 1; j < i; j++) {
            t *= 1 - a[j].second;
        }
        f[0][i] = t;
        g[0][i] = f[0][i] * Point::cross(a[0].first, a[i].first);
    }
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k < i; k++) {
                if (Point::cross(a[k].first, a[i].first, a[j].first) > 0) {
                    double t = a[j].second;
                    // The points between i and j are not chosen
                    for (int p = i + 1; p < j; p++) {
                        if (Point::cross(a[i].first, a[p].first, a[j].first) > 0) {
                            t *= 1 - a[p].second;
                        }
                    }
                    f[i][j] += f[k][i] * t;
                    g[i][j] += g[k][i] * t;
                }
            }
            g[i][j] += f[i][j] * Point::cross(a[i].first, a[j].first);
        }
    }
    double ans = 0;
    for (int i = 1; i < n - 1; i++) {
        ans += g[i][n - 1];
    }
    return ans / 2;
}
