#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

struct point {
	int x, y;
	point() {}
	point(int x, int y) : x(x), y(y) {}
	inline point operator - (const point &b) const {
		return point(x - b.x, y - b.y);
	}
	inline friend LL cross(const point &a, const point &b) {
		return (LL)a.x * b.y - (LL)a.y * b.x;
	}
};

inline int inMod(int x, int mo) {
	if (x < 0)   x += mo;
	if (x >= mo) x -= mo;
	return x;
}

class ConvexPolygonGame {
private :
	static const int LIM = 200000;
	int n, Xmin, Xmax;
	vector<point> pool;
	inline bool colinear(const point &a, const point &b, const point &c) {
		return cross(c - a, b - a) == 0;
	}
	inline double getY(const point &a, const point &b, int x) {
		double p = (double) (b.y - a.y) * (x - a.x), q = b.x - a.x;
		return p / q + a.y;
	}
public :
	//博弈，计算几何
	//如果先手可以操作，则先手一定必胜（反设后手有必胜策略，先手可以模仿）
	//问题转换为多边形内部的格点是否共线
	string winner(vector<int> px, vector<int> py) {
		Xmin = *min_element(px.begin(), px.end());
		Xmax = *max_element(px.begin(), px.end());
		n = px.size();
		rep (x, Xmin, Xmax) {				//扫描每个横坐标，统计共有多少格点
			int sy = -300000, my = 300000;
			rep (i, 0, n-1) {				//计算每条线段和扫描线的交点
				point a(px[i], py[i]);
				point b(px[inMod(i+1, n)], py[inMod(i+1, n)]);
				if (a.x < b.x) {
					if (x == a.x) {
						sy = a.y + 1;
					} else if (x == b.x) {
						sy = b.y + 1;
					} else if (a.x < x && x < b.x) {
						upmax(sy, (int) ceil(getY(a, b, x)));
					}
				} else if (a.x > b.x) {
					if (x == a.x) {
						my = a.y - 1;
					} else if (x == b.x) {
						my = b.y - 1;
					} else if (a.x > x && x > b.x) {
						upmin(my, (int) floor(getY(a, b, x)));
					}
				} else if (x == a.x) {
					sy = min(a.y, b.y) + 1;
					my = max(a.y, b.y) - 1;
				}
			}
			if (sy <= my) {
				int cnt = my - sy + 1;
				if (pool.size() + cnt > LIM) {		//如果多边形内格点多于200000，则一定有不共线的三点
					return "Masha";
				}
				rep (y, sy, my) {
					pool.pb(point(x, y));
				}
			}
		}
		rep (i, 2, pool.size()-1) {
			if (!colinear(pool[0], pool[1], pool[i])) {
				return "Masha";
			}
		}
		return "Petya";
	}
};
