#include <algorithm>
#include <vector>

class Point {
  public:
    int x = 0;
    int y = 0;

    Point() { }
    Point(int x_, int y_) : x(x_), y(y_) { }

    static long long cross(const Point &x, const Point &y);
    static long long cross(const Point &x, const Point &y, const Point &z);
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

long long Point::cross(const Point &x, const Point &y)
{
    return (long long)x.x * y.y - (long long)x.y * y.x;
}

long long Point::cross(const Point &x, const Point &y, const Point &z)
{
    return cross(y - x, z - x);
}

class EnclosingTriangle {
  public:
    long long getNumber(int m, std::vector<int> x, std::vector<int> y);

  private:
    bool checkLeft(const Point &x, const Point &y, const std::vector<Point> &c);
};

long long EnclosingTriangle::getNumber(int m, std::vector<int> x, std::vector<int> y)
{
    std::vector<Point> c(x.size());
    for (int i = 0; i < (int)x.size(); i++) {
        c[i] = Point(x[i], y[i]);
    }
    int p = 4 * m;
    std::vector<Point> a(p);
    for (int i = 0; i < m; i++) {
        a[i] = Point(i, 0);
    }
    for (int i = 0; i < m; i++) {
        a[m + i] = Point(m, i);
    }
    for (int i = 0; i < m; i++) {
        a[2 * m + i] = Point(m - i, m);
    }
    for (int i = 0; i < m; i++) {
        a[3 * m + i] = Point(0, m - i);
    }
    // Range of possible edges
    std::vector<int> nextpos(2 * p);
    for (int i = 0; i < p; i++) {
        int u = std::max(i + 1, i ? nextpos[i - 1] : 0);
        while (checkLeft(a[i], a[u % p], c)) {
            u = u + 1;
        }
        nextpos[i] = u;
    }
    for (int i = 0; i < p; i++) {
        nextpos[i + p] = nextpos[i] + p;
    }
    long long ans = 0;
    // Range of possible B with at least one C available
    int cur1start = 0;
    int cur1end = 0;
    // Range of possible C
    int cur2pos = 0;
    long long s = 0;
    for (int i = 0; i < p; i++) {
        if (cur1start == i) {
            if (cur1end == cur1start) {
                cur1end++;
            } else {
                s -= nextpos[cur1start] - cur2pos;
            }
            cur1start++;
        }
        while (cur1end != nextpos[i]) {
            if (nextpos[cur1end] <= cur2pos) {
                cur1start++;
            } else {
                s += nextpos[cur1end] - cur2pos;
            }
            cur1end++;
        }
        while (nextpos[cur2pos] <= i + p) {
            s -= cur1end - cur1start;
            cur2pos++;
            while (cur1start < cur1end && nextpos[cur1start] == cur2pos) {
                cur1start++;
            }
        }
        ans += s;
        // Remove invalid solutions
        if (nextpos[nextpos[i] - 1] - 1 == i + p) {
            ans -= 2;
        }
    }
    return ans / 3;
}

bool EnclosingTriangle::checkLeft(const Point &x, const Point &y, const std::vector<Point> &c)
{
    for (const auto &p : c) {
        if (Point::cross(x, y, p) < 0) {
            return false;
        }
    }
    return true;
}
