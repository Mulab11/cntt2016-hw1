#include <bits/stdc++.h>

#define MOD 10007 

using namespace std ; 

typedef long long LL  ;  

const int MAXN = 510   ; 

const double pi = acos(-1) ; 

struct Point {
		double x,y ; 
		Point(double a_ = 0 , double b_ = 0 ) {x = a_, y = b_ ;  }
} p[MAXN] ; 

Point operator +(const Point &a,const Point &b) {
		return Point(a.x + b.x,a.y + b.y) ; 
}

Point operator -(const Point &a,const Point &b) {
		return Point(a.x - b.x,a.y - b.y) ; 
}

Point operator *(const Point &a,const double &b) {
		return Point(a.x * b,a.y * b) ; 
}

Point operator *(const double &a,const Point &b) {
		return b * a ; 
}

double operator *(const Point &a,const Point &b) {
		return a.x * b.x + a.y * b.y ; 
}

double operator ^(const Point &a,const Point &b) {
		return a.x * b.y - a.y * b.x ; 
}

bool vis[MAXN][MAXN] ; 
int c[MAXN],h[MAXN][MAXN][2],f[MAXN][MAXN],g[MAXN][MAXN] ; 
LL allpick[MAXN][MAXN],callpick[MAXN][MAXN] ; 

class FencingPenguins {
		public:

				int countWays(int n, int radius, vector <int> x, vector <int> y, string color) {

						int m = x.size() ; 

						for(int i = 0 ; i < n ; i ++) p[i] = radius * Point(cos(i * 2 * pi / n),sin(i * 2 * pi / n)) ; 
						for(int i = 0 ; i < m ; i ++) {
								if (color[i] >= 'a' && color[i] <= 'z') c[i] = color[i] - 'a' ;  
								else c[i] = color[i] - 'A' + 26 ; 
						}
						for(int i = 0 ; i < n ; i ++)
								for(int j = 0 ; j < n ; j ++)
										if (i != j)
												for(int k = 0 ; k < m ; k ++)
														if (((Point(x[k],y[k]) - p[i]) ^ (p[j] - p[i])) > 0) {
																allpick[i][j] |= (1LL << k) ; 
																callpick[i][j] |= (1LL << c[k]) ; 
														}
						if (allpick[0][n - 1] != (1LL << m) - 1) return 0 ; 
						for(int i = 0 ; i < n ; i ++)
								for(int j = i + 1 ; j < n ; j ++)
										if (callpick[i][j] & callpick[j][i]) vis[i][j] = 0 ;  else vis[i][j] = 1 ; 
						for(int i = 0 ; i < n ; i ++) h[i][i][1] = 1 ; 
						for(int l = n - 1 ; l >= 0 ; l --)
								for(int r = l + 1 ; r < n ; r ++) {
										for(int d = 0 ; d < 2 ; d ++)
												for(int L = l + 1 ; L <= r ; L ++)
														if (vis[l][L]) {
																int ng = d | bool(allpick[l][r] & allpick[r][L] & allpick[L][l]) ; 
																int cur = h[L][r][ng] ; 
																if (allpick[l][L]) {
																		if (allpick[l][L] & allpick[L - 1][l + 1]) cur = 0 ;  else
																				cur = cur * 1LL * f[l + 1][L - 1] % MOD ; 
																}
																h[l][r][d] = (h[l][r][d] + cur) % MOD ; 
														}
										for(int R = l + 1 ; R <= r ; R ++)
												if (vis[l][R]) {
														if (allpick[l][r] & allpick[r][R + 1] & allpick[R][l]) continue ; 
														if (!(allpick[l][r] & allpick[R][l]))
																g[l][r] = (g[l][r] + h[l][R][0]) % MOD ;  else
																		g[l][r] = (g[l][r] + h[l][R][0] * 1LL * f[R + 1][r]) % MOD ; 
												}
										for(int L = l ; L <= r ; L ++) {
												if (allpick[l][r] & allpick[r][L]) continue ; 
												f[l][r] = (f[l][r] + g[L][r]) % MOD ; 
										}
								}
						return f[0][n - 1] ; 
				}
} ; 
