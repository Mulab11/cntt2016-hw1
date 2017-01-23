#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 240005, MN = 25;

class EnclosingTriangle{
public:
	struct Point{
		int x, y;
		Point(){}
		Point(int a, int b): x(a), y(b) {}
		Point operator - (const Point &rhs) const{
			return Point(x - rhs.x, y - rhs.y);
		}
	}p1[MAXN], p2[MN];
	int f[MAXN], g[MAXN], n, m; LL pf[MAXN];
	inline LL Cross(Point a, Point b){return LL(a.x) * b.y - LL(a.y) * b.x;}
	inline bool check(Point &x, Point &y){
		Point d = y - x;
		for(int i = 1; i <= m; ++ i)
			if(Cross(d, p2[i] - x) < 0LL)
				return false;
		return true;
	}
	LL getNumber(int n_, vector <int> x, vector <int> y){
		int i, j, k; LL ans = 0LL;
		for(i = n = 0; i < n_; ++ i)
			p1[++ n] = Point(i, 0);
		for(i = 0; i < n_; ++ i)
			p1[++ n] = Point(n_, i);
		for(i = 0; i < n_; ++ i)
			p1[++ n] = Point(n_ - i, n_);
		for(i = 0; i < n_; ++ i)
			p1[++ n] = Point(0, n_ - i);
		for(i = 0, m = x.size(); i < m; ++ i)
			p2[i + 1] = Point(x[i], y[i]);
		for(i = j = 1, k = 2, pf[0] = 0; i <= n; ++ i){
			while(j < n && check(p1[i], p1[j + 1])) ++ j;
			while(k <= n && !check(p1[k], p1[i])) ++ k;
			f[i] = j, g[i] = k;
			pf[i] = pf[i - 1] + f[i];
		}
		for(i = j = 1; i < n; ++ i){
			ans += max(f[f[i]] - max(f[i] + 1, g[i]) + 1, 0);
			while(j <= n && f[j] < g[i]) ++ j;
			if(j < f[i]){
				j = max(j, i + 1);
				ans += pf[f[i] - 1] - pf[j - 1] - LL(g[i] - 1) * (f[i] - j);
			}
		} return ans;
	}
};
