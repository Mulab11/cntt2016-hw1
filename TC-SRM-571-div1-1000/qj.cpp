#include <bits/stdc++.h>

#define fst first
#define snd second

using namespace std;

typedef long long i64;
typedef long double f80;
typedef std::pair<f80, f80> Range;

const int N = 50 + 10;
const f80 eps = 1e-12L;

class CandyOnDisk {
  int n;
  struct Point {
    int x, y;
    Point(int _x, int _y): x(_x), y(_y) {}
    inline bool operator== (const Point &rhs) const {
      return x == rhs.x && y == rhs.y;
    }
  };
  inline f80 sqr(f80 x) { return x * x; }
  inline f80 dist(const Point &a, const Point &b) { return sqrtl(sqr(a.x - b.x) + sqr(a.y - b.y)); }
  inline int sgn(f80 x) {
    if (fabsl(x) < eps) return 0;
    return x > 0.L ? 1 : -1;
  }
  std::vector<Point> p;
  std::vector<int> r;
  bool solve(int s, int t) {
    std::vector<Range> range(n);
    std::vector<int> q;
    std::vector<bool> flag(n);
    for (int i = 0; i < n; ++i) range[i] = std::make_pair(1. / 0., -1. / 0.);
    range[s] = std::make_pair(0., 0.);
    // the set of reachable points in a circle must be a ring
    // so we save the min / max radius of the ring
    q.push_back(s);
    flag[s] = true;
    for (int i = 0; i < q.size(); ++i) {
      int a = q[i];
      flag[a] = false;
      for (int b = 0; b < n; ++b) {
        if (a == b) continue;
        f80 c = dist(p[a], p[b]);
        Range temp(std::min(fabsl(c - range[a].fst), fabsl(c - range[a].snd)), c + range[a].snd);
        if (range[a].fst <= c && c <= range[a].snd) temp.fst = 0.;
        // intersection of a ring and a circle
        temp.snd = std::min<f80>(temp.snd, r[b]);
        if (sgn(temp.fst - temp.snd) > 0) continue;
        if (p[a] == p[b]) temp = range[a]; else temp = std::make_pair(std::max(0.L, c - r[a]), std::min<f80>(r[b], c + r[a]));
        // skip some steps
        // calculate the final status
        temp.fst = std::min(temp.fst, range[b].fst);
        temp.snd = std::max(temp.snd, range[b].snd);
        if (sgn(temp.fst - range[b].fst) || sgn(temp.snd - range[b].snd)) {
          range[b] = temp;
          if (!flag[b]) q.push_back(b), flag[b] = true;
        }
      }
    }
    return range[t].fst <= range[t].snd;
  }
 public:
  string ableToAchieve(vector<int> x, vector<int> y, vector<int> _r, int sx, int sy, int tx, int ty) {
    n = x.size();
    for (int i = 0; i < n; ++i) p.push_back(Point(x[i], y[i]));
    r = _r;
    p.push_back(Point(sx, sy));
    p.push_back(Point(tx, ty));
    r.push_back(0);
    r.push_back(0);
    n += 2;
    return solve(n - 2, n - 1) ? "YES" : "NO";
  }
};
