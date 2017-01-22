/*
	Expected value
	dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 63;
struct pack{double r, p, s;}a[MAXN], f[MAXN][MAXN][MAXN];
pack operator *(const pack& a, const double &b){return pack{a.r * b, a.p * b, a.s * b};}
pack operator /(const pack& a, const double &b){return a * (1 / b);}
pack operator +=(pack& a, const pack& b){return a = pack{a.r + b.r, a.p + b.p, a.s + b.s};}
double eval(const pack& a){return max({a.r * 3 + a.p, a.p * 3 + a.s, a.s * 3 + a.r});}
double g[MAXN][MAXN][MAXN], h[MAXN][MAXN][MAXN];
class RockPaperScissors {
	public:
	double bestScore(vector <int> r0, vector <int> p0, vector <int> s0) {
		double ret = 0; int n = r0.size();
		memset(f, 0, sizeof f); memset(g, 0, sizeof g); memset(h, 0, sizeof h);
		g[0][0][0] = h[0][0][0] = 1;
		rep(i, 0, n - 1) a[i + 1] = pack{(double)r0[i], (double)p0[i], (double)s0[i]} / 300;
		rep(i, 1, n) red(r, i, 0) red(p, i - r, 0) red(s, i - r - p, 0){
			f[r][p][s] += a[i] * g[r][p][s];
			if (r) f[r][p][s] += f[r - 1][p][s] * a[i].r, g[r][p][s] += g[r - 1][p][s] * a[i].r;
			if (p) f[r][p][s] += f[r][p - 1][s] * a[i].p, g[r][p][s] += g[r][p - 1][s] * a[i].p;
			if (s) f[r][p][s] += f[r][p][s - 1] * a[i].s, g[r][p][s] += g[r][p][s - 1] * a[i].s;
		}
		rep(r, 0, n - 1) rep(p, 0, n - 1 - r) rep(s, 0, n - 1 - r - p) if (g[r][p][s]){
			f[r][p][s] = f[r][p][s] / g[r][p][s] / (n - r - p - s);
			h[r + 1][p][s] += h[r][p][s] * f[r][p][s].r;
			h[r][p + 1][s] += h[r][p][s] * f[r][p][s].p;
			h[r][p][s + 1] += h[r][p][s] * f[r][p][s].s;
			ret += eval(f[r][p][s]) * h[r][p][s];
		}
		return ret;
	}
};

/*
	Tired
*/
