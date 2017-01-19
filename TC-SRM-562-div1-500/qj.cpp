#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

struct Point {
  int x, y;
  Point() {}
  Point(int _x, int _y): x(_x), y(_y) {}
  inline double arg() const { return atan2(y, x); }
  inline double norm() const { return sqrt((double)x * x + (double)y * y); }
  friend inline Point operator- (const Point &lhs, const Point &rhs) { return Point(lhs.x - rhs.x, lhs.y - rhs.y); }
  inline bool operator< (const Point &rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
  }
  friend i64 cross(const Point &o, const Point &a, const Point &b) {
    return ((i64)a.x - o.x) * (b.y - o.y) - ((i64)a.y - o.y) * (b.x - o.x);
  }
  friend i64 dot(const Point &o, const Point &a, const Point &b) {
    return ((i64)a.x - o.x) * (b.x - o.x) + ((i64)a.y - o.y) * (b.y - o.y);
  }
};

class CheckerFreeness {
  void parse(const std::vector<std::string> &a, std::vector<int> &res) {
    res.clear();
    std::string s;
    for (int i = 0; i < a.size(); ++i) s += a[i];
    std::stringstream ss(s);
    for (int x; ss >> x;) res.push_back(x);
  }
  inline double sqr(double x) { return x * x; }
  std::vector<Point> p[2];
  typedef std::pair<double, double> Info;
  double calc(const Point &a, const Point &o, const Point &b) {
    return acos(dot(o, a, b) / (a - o).norm() / (b - o).norm());
  }
  bool solve() {
    // scan
    Point o = p[0][0], a = p[1][0];
    std::vector<Info> q[2];
    for (int i = 0; i < 2; ++i)
      for (int j = 1; j < p[i].size(); ++j)
        if (cross(o, a, p[i][j]) > 0) q[i].push_back(Info(calc(a, o, p[i][j]), calc(p[i][j], a, o)));
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j + 1 < q[i].size(); ++j) {
        if (q[i][j] > q[i][j + 1]) {
          std::rotate(q[i].begin(), q[i].begin() + j + 1, q[i].end());
          break;
        }
      }
    }
    double mx = -1.;
    for (int i = 0, j = 0; i < q[1].size(); ++i) {
      Info info = q[1][i];
      for (; j < q[0].size() && q[0][j].first <= info.first; ++j) mx = std::max(mx, q[0][j].second);
      if (mx > info.second) return true;
    }
    return false;
  }
 public:
  string isFree(vector<string> whiteX, vector<string> whiteY, vector<string> blackX, vector<string> blackY) {
    std::vector<int> x[2], y[2];
    parse(whiteX, x[0]);
    parse(whiteY, y[0]);
    parse(blackX, x[1]);
    parse(blackY, y[1]);
    std::vector<Point> temp[2];
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < x[i].size(); ++j)
        temp[i].push_back(Point(x[i][j], y[i][j]));
    for (int i = temp[0].size(); i--; std::rotate(temp[0].begin(), temp[0].begin() + 1, temp[0].end())) {
      // enumerate one of the points
      std::vector< std::pair<double, Point> > pool;
      for (int j = 1; j < temp[0].size(); ++j) pool.push_back(std::make_pair((temp[0][j] - temp[0][0]).arg(), temp[0][j]));
      std::sort(pool.begin(), pool.end());
      p[0].clear();
      p[0].push_back(temp[0][0]);
      for (int j = 0; j < pool.size(); ++j) p[0].push_back(pool[j].second);
      pool.clear();
      for (int j = 0; j < temp[1].size(); ++j) pool.push_back(std::make_pair((temp[1][j] - temp[0][0]).arg(), temp[1][j]));
      std::sort(pool.begin(), pool.end());
      p[1].clear();
      for (int j = 0; j < pool.size(); ++j) p[1].push_back(pool[j].second);
      for (int j = p[1].size(); j--; std::rotate(p[1].begin(), p[1].begin() + 1, p[1].end())) if (solve()) return "NO"; // enumerate a white point
    }
    return "YES";
  }
};
