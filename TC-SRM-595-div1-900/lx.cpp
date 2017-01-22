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

const int inf = 0x3f3f3f3f;
const int N = 1e5 + 10;

inline int sqr(int x) {
	return x * x;
}

struct point {
	int x, y;
	point() {}
	point(int x, int y) : x(x), y(y) {}
	inline point operator - (const point &b) const {
		return point(x - b.x, y - b.y);
	}
	inline friend int cross(const point &a, const point &b) {
		return (LL)a.x * b.y - (LL)a.y * b.x;
	}
	inline friend int dis2(const point &a) {
		return sqr(a.x) + sqr(a.y);
	}
};

class Constellation {
private :
	vector<point> ps;
	int n;
public :
	// 概率与期望，枚举
	// 凸包的面积可以用有向线段的面积的和计算，枚举每条有向线段，计算它出现在凸包上的概率，乘以它的贡献，加起来即可得到期望
	double expectation(vector<int> X, vector<int> Y, vector<int> prob) {
		n = X.size();
		double ans = 0;
		rep (i, 0, n - 1) {
			ps.pb(point(X[i], Y[i]));
		}
		rep (i, 0, n - 1) {
			rep (j, 0, n - 1) if (i != j) {
				// 计算有向线段 (i, j) 出现在凸包上的概率
				double p = prob[i] * prob[j] / 1000000.0;
				rep (k, 0, n - 1) {
					if (k != i && k != j) {
						int tmp = cross(ps[j] - ps[i], ps[k] - ps[i]);
						if (tmp < 0 || 
								(tmp == 0 && dis2(ps[j] - ps[i]) < max(dis2(ps[k] - ps[j]), dis2(ps[k] - ps[i])))) {
							p *= (1000 - prob[k]) / 1000.0;
						}
					}
				}
				ans += p * cross(ps[i], ps[j]);
			}
		}
		return ans / 2.0;
	}
};
