/*
	Geometry
	Interval dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
#define X first
#define Y second
using namespace std;
typedef long long LL;
typedef pair<double, double> pt;
const int MAXN = 233;
const double pi = acos(-1);
const LL MOD = 100007;
pt operator -(pt a, pt b){
	return pt(a.X - b.X, a.Y - b.Y);
}
double cross(pt a, pt b){
	return a.X * b.Y - a.Y * b.X;
}
double cross(pt o, pt a, pt b){
	return cross(a - o, b - o);
}
pt a[MAXN], b[MAXN];
LL s[MAXN][MAXN], sc[MAXN][MAXN], f[MAXN][MAXN], g[MAXN][MAXN], h[MAXN][MAXN][2];
bool valid[MAXN][MAXN];
class FencingPenguins {
	public:
	int countWays(int n, int r, vector <int> x, vector <int> y, string c) {
		memset(f, 0, sizeof f); memset(g, 0, sizeof g); memset(h, 0, sizeof h);
		memset(s, 0, sizeof s); memset(sc, 0, sizeof sc);
		int m = x.size();
		rep(i, 0, m - 1) b[i] = pt(x[i], y[i]), c[i] = c[i] >= 'a' ? 'z' - c[i] : 'Z' - c[i] + 26;
		rep(i, 0, n - 1) a[i] = pt(r * cos(2 * pi / n * i), r * sin(2 * pi / n * i));
		rep(i, 0, n - 1) rep(j, 0, n - 1) rep(k, 0, m - 1) // find the set of points && colors to the left of i->j
			if (cross(a[i], a[j], b[k]) >= 0)
				s[i][j] |= 1ll << k, sc[i][j] |= 1ll << c[k];
		rep(i, 0, n - 1) if (s[i][(i + 1) % n] != (1ll << m) - 1) return 0; // spj : something is outside the polygon
		rep(i, 0, n - 1) rep(j, 0, n - 1) valid[i][j] = !(sc[i][j] & sc[j][i]); // i<->j is valid if it doesn't separate any color
		rep(i, 0, n - 1) h[i][i][1] = 1; // consider this as a valid self-loop for an initial state
		rep(len, 1, n - 1) rep(i, 0, n - 1 - len){
			int j = i + len;
			rep(d, 0, 1) rep(k, i + 1, j) if (valid[i][k]){
				LL v = h[k][j][d || (s[i][k] & s[k][j] & s[j][i])]; // judge if any point is inside  
				if (!s[k][i]) h[i][j][d] += v; // no other points
				else if (i + 3 < k && !(s[k][i] & s[i + 1][k - 1])) h[i][j][d] += v * f[i + 1][k - 1]; // otherwise
			}
			rep(d, 0, 1) h[i][j][d] %= MOD;
			red(k, j, i + 2) if (valid[i][k]){ // link another point k
				if (!(s[j][i] & s[i][k])) g[i][j] += h[i][k][0];
				else if (k < j - 2 && !(s[j][i] & s[i][k] & s[k + 1][j])) g[i][j] += f[k + 1][j] * h[i][k][0];
			}
			g[i][j] %= MOD;
			rep(k, i, j) if(!(s[j][i] & s[k][j])) f[i][j] += g[k][j];
			f[i][j] %= MOD;
		}
		return f[0][n - 1];
	}
};

/*
	Desire drive
*/
