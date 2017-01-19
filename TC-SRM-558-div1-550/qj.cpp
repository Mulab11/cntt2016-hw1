#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

class Ear {
  std::vector<int> parse(const std::vector<std::string> &pool) {
    std::vector<int> res;
    std::string s;
    for (int i = 0; i < pool.size(); ++i) s += pool[i];
    std::stringstream ss(s);
    for (int x; ss >> x;) res.push_back(x);
    return res;
  }
  struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y): x(_x), y(_y) {}
    inline bool operator< (const Point &rhs) const {
      return y < rhs.y;
    }
  };
  inline int calc(int a, int n) { return a * n + n * (n - 1) / 2; } // a + (a + 1) + (a + 2) + ... + (a + n - 1)
 public:
  i64 getCount(vector<string> redX, vector<string> blueX, vector<string> blueY) {
    std::vector<int> x = parse(redX), pool[2] = {parse(blueX), parse(blueY)};
    std::vector<Point> p;
    for (int i = 0; i < pool[0].size(); ++i) p.push_back(Point(pool[0][i], pool[1][i]));
    std::sort(p.begin(), p.end());
    std::sort(x.begin(), x.end());
    i64 res = 0;
    for (int i = 0; i < p.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        // (t, 0), (p[i].x, p[i].y), (p[j].x, p[j].y)
        // (p[i].x - t) / p[i].y = (p[j].x - p[i].x) / (p[j].y - p[i].y)
        // t = p[i].x - (p[j].x - p[i].x) / (p[j].y - p[i].y) * p[i].y
        i64 numer = p[i].x * (p[j].y - p[i].y) - p[i].y * (p[j].x - p[i].x), denom = p[j].y - p[i].y;
        int a0 = p[j].x - 1, a1 = numer / denom - (numer % denom == 0);
        int b0 = p[j].x + 1, b1 = numer / denom + 1;
        a1 = std::min(a1, std::min(p[j].x - 1, p[i].x - 1));
        b1 = std::max(b1, std::max(p[j].x + 1, p[i].x + 1));
        a0 = std::upper_bound(x.begin(), x.end(), a0) - x.begin();
        a1 = std::upper_bound(x.begin(), x.end(), a1) - x.begin();
        b0 = x.end() - std::lower_bound(x.begin(), x.end(), b0);
        b1 = x.end() - std::lower_bound(x.begin(), x.end(), b1);
        res += (i64)calc(a0 - a1, a1) * calc(b0 - b1, b1);
      }
    }
    return res;
  }
};
