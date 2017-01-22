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

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;
const int N = 234355;

struct point {
	int x, y;
	point() {}
	point(int x, int y) : x(x), y(y) {}
	inline point operator + (const point &b) const {
		return point(x + b.x, y + b.y);
	}
	inline point operator - (const point &b) const {
		return point(x - b.x, y - b.y);
	}
	inline LL friend cross(const point &a, const point &b) {
		return (LL) a.x * b.y - (LL) a.y * b.x;
	}
};

class EnclosingTriangle {
private :
	point p[21], cir[N];
	int n, m, tot;
	int nxt[N], pre[N], tag[N];
public :
	LL getNumber(int m, vector<int> xs, vector<int> ys) {
		this->m = m;
		n = xs.size();
		rep (i, 0, n - 1)  p[i] = point(xs[i], ys[i]);
		rep (i, 0, m - 1)  cir[tot++] = point(i, 0);
		rep (i, 0, m - 1)  cir[tot++] = point(m, i);
		down (i, m, 1)  cir[tot++] = point(i, m);
		down (i, m, 1)  cir[tot++] = point(0, i);
		int cur = 1;
		rep (i, 0, tot - 1) {
			point best = p[0];
			rep (j, 1, n - 1) if (cross(p[j] - cir[i], best - cir[i]) > 0)
				best = p[j];
			while (cur < tot && cross(cir[cur] - cir[i], best - cir[i]) >= 0)
				++cur;
			nxt[i] = cur - 1;
		}
		cur = 1;
		rep (i, 0, tot - 1) {
			point best = p[0];
			rep (j, 1, n - 1) if (cross(p[j] - cir[i], best - cir[i]) < 0)
				best = p[j];
			while (cur < tot && cross(cir[cur] - cir[i], best - cir[i]) > 0)
				++cur;
			pre[i] = cur;
		}
		LL res = 0, now = 0, cnt = 0;
		int pp = 1, np = 1;
		rep (i, 0, tot - 1) {
			while (pp < pre[i]) {
				cnt -= now;
				now -= tag[pp];
				++pp;
			}
			if (nxt[i] >= pp) {
				res += tot - pp - 1;
				if (i) {
					cnt -= nxt[i] - pp + 1;
					tag[nxt[i]]--;
					now--;
				}
			}
			while (np < min(nxt[i] + 1, pp)) {
				if (nxt[np] >= pp) {
					cnt += nxt[np] - pp + 1;
					tag[nxt[np]]++;
					now++;
				}
				++np;
			}
			res += cnt;
		}
		return res;
	}
};
