#include <algorithm>
#include <sstream>
#include <string>
#include <utility>
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

class CheckerFreeness {
  public:
    std::string isFree(std::vector<std::string> whiteX, std::vector<std::string> whiteY, std::vector<std::string> blackX, std::vector<std::string> blackY);

  private:
    std::string isFree2(const std::vector<Point> &w, const std::vector<Point> &b);
    bool hasChecker(Point p1, Point p2, const std::vector<Point> &a);
};

std::string CheckerFreeness::isFree(std::vector<std::string> whiteX, std::vector<std::string> whiteY, std::vector<std::string> blackX, std::vector<std::string> blackY)
{
    std::string swx;
    for (const auto &x : whiteX) {
        swx += x;
    }
    std::string swy;
    for (const auto &x : whiteY) {
        swy += x;
    }
    std::string sbx;
    for (const auto &x : blackX) {
        sbx += x;
    }
    std::string sby;
    for (const auto &x : blackY) {
        sby += x;
    }
    int val;
    std::vector<int> wx;
    std::istringstream sswx(swx);
    while (sswx >> val) {
        wx.push_back(val);
    }
    std::vector<int> wy;
    std::istringstream sswy(swy);
    while (sswy >> val) {
        wy.push_back(val);
    }
    std::vector<int> bx;
    std::istringstream ssbx(sbx);
    while (ssbx >> val) {
        bx.push_back(val);
    }
    std::vector<int> by;
    std::istringstream ssby(sby);
    while (ssby >> val) {
        by.push_back(val);
    }
    std::vector<Point> w(wx.size());
    for (int i = 0; i < (int)wx.size(); i++) {
        w[i] = Point(wx[i], wy[i]);
    }
    std::vector<Point> b(bx.size());
    for (int i = 0; i < (int)bx.size(); i++) {
        b[i] = Point(bx[i], by[i]);
    }
    return isFree2(w, b);
}

std::string CheckerFreeness::isFree2(const std::vector<Point> &w, const std::vector<Point> &b)
{
    // Enumerate the pair of white points
    for (int i = 0; i < (int)w.size(); i++) {
        for (int j = i + 1; j < (int)w.size(); j++) {
            if (hasChecker(w[i], w[j], b)) {
                return "NO";
            }
        }
    }
    return "YES";
}

bool CheckerFreeness::hasChecker(Point p1, Point p2, const std::vector<Point> &a)
{
    std::vector<Point> al;
    std::vector<Point> ar;
    for (auto x : a) {
        if (Point::cross(p1, p2, x) > 0) {
            al.push_back(x);
        } else {
            ar.push_back(x);
        }
    }
    std::vector<Point> ray1 = al;
    std::vector<Point> ray2 = al;
    Point center;
    auto cmp = [center](const Point &x, const Point &y) {
        return Point::cross(center, x, y) > 0;
    };
    center = p1;
    std::sort(ray1.begin(), ray1.end(), cmp);
    center = p2;
    std::sort(ray2.begin(), ray2.end(), cmp);
    std::vector<std::pair<Point, int>> u(ar.size());
    for (int i = 0; i < (int)ar.size(); i++) {
        u[i] = std::make_pair(ar[i], 0);
    }
    auto cmp2 = [center](const std::pair<Point, int> &x, const std::pair<Point, int> &y) {
        return Point::cross(center, x.first, y.first) > 0;
    };
    int cur;
    center = p1;
    std::sort(u.begin(), u.end(), cmp2);
    cur = 0;
    for (auto &x : u) {
        while (cur < (int)ray1.size() && Point::cross(p1, ray1[cur], x.first) < 0) {
            cur++;
        }
        x.second += cur;
    }
    center = p2;
    std::sort(u.begin(), u.end(), cmp2);
    cur = 0;
    for (auto &x : u) {
        while (cur < (int)ray2.size() && Point::cross(p2, ray2[cur], x.first) < 0) {
            cur++;
        }
        x.second -= cur;
    }
    for (auto x : u) {
        if (x.second > 0) {
            return true;
        }
    }
    return false;
}
