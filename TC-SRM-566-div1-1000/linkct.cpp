#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 305, MAXM = 105;
const double PI = acos(-1.0);
const LL MOD = 100007LL;

class FencingPenguins{
public:
	struct Point{
		double x, y;
		Point(){}
		Point(double a, double b): x(a), y(b) {}
		Point operator - (const Point &rhs) const{
			return Point(x - rhs.x, y - rhs.y);
		}
		Point rotate(double ang){
			return Point(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));
		}
	}p[MAXN];
	double Cross(const Point a, const Point b){
		return a.x * b.y - a.y * b.x;
	}
	struct Penguin{
		Point p; int c;
		bool operator < (const Penguin &rhs) const{
			return c < rhs.c;
		}
	}pg[MAXM];
	LL dp[MAXN][MAXN], f[MAXN][MAXN], g[MAXN][MAXN], lft[MAXN][MAXN];
	int G[MAXN][MAXN], rht[MAXN][MAXN];
	bool ok[MAXN][MAXN][MAXN];
	inline int sgn(double x){return x > 0.0 ? 1 : -1;}
	inline void update(LL &a, LL b){a = (a + b) % MOD;}
	int countWays(int n, int r, vector <int> x, vector <int> y, string col){
		int i, j, k, L, m = x.size(); double ang;
		for(i = 0; i < m; ++ i){
			pg[i + 1].p = Point(x[i], y[i]);
			pg[i + 1].c = col[i];
		} sort(pg + 1, pg + 1 + m);
		memset(G, 0, sizeof(G));
		memset(ok, false, sizeof(ok));
		memset(rht, 0, sizeof(rht));
		memset(lft, 0, sizeof(lft));
		p[1] = Point(r, 0), ang = 2 * PI / n;
		for(i = 2; i <= n; ++ i)
			p[i] = p[1].rotate(ang * (i - 1));
		for(i = 1; i <= n; ++ i)
			for(j = i + 1; j <= n; ++ j){
				for(k = 1; k <= m; ++ k)
					if(Cross(p[j] - p[i], pg[k].p - p[i]) < 0.0) ++ rht[i][j];
					else lft[i][j] |= 1LL << k;
				for(k = 2; k <= m; ++ k){
					if(pg[k].c != pg[k - 1].c) continue;
					if(sgn(Cross(p[j] - p[i], pg[k].p - p[i])) != sgn(Cross(p[j] - p[i], pg[k - 1].p - p[i]))) break;
				} if(k <= m) continue;
				G[i][j] = G[j][i] = true; //Preprocess valid fences
			}
		for(i = 1; i <= n; ++ i)
			for(j = i + 1; j <= n; ++ j)
				for(k = j + 1; k <= n; ++ k)
					if(lft[i][j] & lft[j][k] & (((1LL << (m + 1)) - 2) ^ lft[i][k])) //Triangles which contain penguin(s)
						ok[i][j][k] = true;
		memset(dp, 0, sizeof(dp));
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		//dp[i][j]: number of ways to contain all penguins in polygon (i, i+1, i+2, .., j, i)
		//f[i][j]: number of ways to contain all penguins in polygon (i, i+1, i+2, .., j, i) and have a single polygon (i, ..., j, i) which hasn't contained any penguins yet
		//g[i][j]: number of ways to contain all penguins in polygon (i, i+1, i+2, .., j, i) and have a single polygon (i, ..., j, i) which has already contained at least one penguin
		for(i = 1; i <= n; ++ i){
			if(rht[i][i + 1]) return 0;
			dp[i][i] = dp[i][i - 1] = dp[i][i + 1] = f[i][i + 1] = 1;
		} if(rht[1][n] != m) return 0; //Penguin outside the regular polygon -- no solution
		for(L = 2; L < n; ++ L)
			for(i = 1; i + L <= n; ++ i){
				j = i + L;
				if(G[i][j] && rht[i][j] == rht[i + 1][j - 1]) f[i][j] = dp[i + 1][j - 1]; //Border case: polygon degenerates to segment
				for(k = i + 1; k < j; ++ k){ //Construct (i, ..., k, j, i) with [k+1, j-1] as subproblem
					if((rht[k][j] > rht[k + 1][j - 1]) || (G[k][j] == 0)) continue;
					update(g[i][j], g[i][k] * dp[k + 1][j - 1] % MOD);
					if(ok[i][k][j]) update(g[i][j], f[i][k] * dp[k + 1][j - 1] % MOD);
					else update(f[i][j], f[i][k] * dp[k + 1][j - 1] % MOD);
				}
				if(!ok[i][i + 1][j]) update(dp[i][j], dp[i + 1][j]); //Point i not connected by any fences
				for(k = i + 2; k < j; ++ k) //Construct (i, ..., k, i) as the first polygon in [i, j]
					if((!(ok[i][k][k + 1] || ok[i][k + 1][j])) && G[i][k])
						update(dp[i][j], g[i][k] * dp[k + 1][j] % MOD);
				if(G[i][j]) update(dp[i][j], g[i][j]);
			}
		return dp[1][n];
	}
};
