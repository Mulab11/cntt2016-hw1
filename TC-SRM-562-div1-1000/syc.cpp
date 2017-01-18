#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <bitset>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define PR pair
#define fi first
#define se second
#define mk make_pair
#define pb push_back
#define REP(i, x, y)   for(int i = (int)(x); i <= (int)(y); i++)
#define FOR(i, x, y)   for(int i = (int)(x); i <  (int)(y); i++)
#define PER(i ,x, y)  for(int i = (int)(x); i >= (int)(y); i--)
#define CH	         ch = getchar()
#define Exit(...)    printf(__VA_ARGS__), exit(0)
#define dln()        fprintf(stderr,"\n")
#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef double	  db;
typedef long long LL;
typedef vector<int> VI;
typedef vector<VI > VII;
typedef PR<int,int> PII;
typedef vector<PII> VPI;
const	int inf=2e9;
const	LL Inf=1e10;
const	int P=1e9+9;
const	int N=45;

inline LL IN(){
	LL x = 0;
	int ch = 0, f = 0;
	for (CH; ch != -1 && (ch < 48 || ch > 57); CH) f = (ch == '-');
	for (; ch >= 48 && ch <= 57; CH) x = (x << 1) + (x << 3) + ch - '0';
	return f ? (-x) : x;
}
template<typename T> inline int chkmin(T &a, const T &b){if(b < a) return a = b, 1; return 0;}
template<typename T> inline int chkmax(T &a, const T &b){if(b > a) return a = b, 1; return 0;}

void renew(int &x, const int &y){
	x += y;
	if(x >= P) x -= P;
	if(x <  0) x += P;
}

int Pow(int x, int y, int p){
	int a = 1;
	for (; y; y >>= 1, x = (LL)x * x %p) if(y & 1) a=(LL)a * x%p;
	return a;
}

int n, K;
int sz[N], fac[N], invfac[N];
VI e[N];

int C(int x, int y){
	if(x < y) return 0;
	return 1LL * fac[x] * invfac[y] % P * invfac[x - y] % P;
}

namespace Work1{
	
	int vis[N];
	
	int dfs(int x){
		int ways = 1;
		for(auto v : e[x]){
			if(vis[v]) continue;
			vis[v] = 1;
			int tmp = dfs(v);
			ways = 1LL * ways * tmp % P;
			ways = 1LL * ways * C(sz[x] + sz[v], sz[v]) % P;
			sz[x] += sz[v];
		}
		sz[x] ++;
		return ways;
	}
	
	int dist[N][N];
	int Main(){
		int ans = 0;
		REP(i, 1, n) REP(j, 1, n) if(i == j) dist[i][j] = 0; else dist[i][j] = 1e9;
		REP(i, 1, n) for(auto v : e[i]) dist[i][v] = 1;
		REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) chkmin(dist[i][j], dist[i][k] + dist[k][j]);
		REP(i, 1, n) REP(j, 1, n)if(dist[i][j] == n - 2 * K + 1){
			memset(sz, 0, sizeof sz);
			memset(vis, 0, sizeof vis);
			REP(k, 1, n) if(dist[i][k] + dist[k][j] == dist[i][j]) vis[k] = 1;
			int F1 = dfs(i);
			int F2 = dfs(j);
			if(sz[i] == K && sz[j] == K){
				ans = (ans + 1LL * F1 * F2) % P;
			}
		}
		return ans;
	}
}

namespace Work2{
	int F[N][N][N][N], G[N][N][N];
	int sub[N], sz[N], fa[N], ff[N];
	int now[N], ans;
	
	void dfs(int x){
		sub[x] = 1;
		for(auto v : e[x]){
			if(v == fa[x])continue;
			fa[v] = x;
			dfs(v);
			sub[x] = 1LL * sub[x] * sub[v] % P;
			sub[x] = 1LL * sub[x] * C(sz[x] + sz[v], sz[v]) % P;
			sz[x] += sz[v];
		}
		sz[x] ++;
	}
	
	void dp1(int x){
		for(auto v : e[x]){
			if(v == fa[x]) continue;
			int SZ = n - sz[x], res = ff[x];
			for(auto w : e[x]) if(w != v && w != fa[x]){
				res = 1LL * res * sub[w] % P;
				res = 1LL * res * C(SZ + sz[w], SZ) % P;
				SZ += sz[w];
			}
			ff[v] = res;
			dp1(v);
		}
	}
	
	void dp2(int x){
		F[x][1][0][0] = 1;
		now[x] = 1;
		for(auto v : e[x]){
			if(v == fa[x]) continue;
			dp2(v);
			memset(G, 0, sizeof G);
			REP(a1, 1, now[x])if(a1 <= K)
			REP(b1, 0, now[x])
			REP(c1, 0, now[x])if(F[x][a1][b1][c1])
			REP(a2, 1, sz[v])if(a2 <= K)
			REP(b2, 0, sz[v])
			REP(c2, 0, sz[v])if(F[v][a2][b2][c2]){
				renew(G[a1 + a2][b1 + b2][c1 + c2], 1LL * F[x][a1][b1][c1] * F[v][a2][b2][c2] % P * C(b1 + b2, b1) % P * C(c1 + c2, c1) % P);
			}
			
			REP(i, 0, now[x])
			REP(j, 0, now[x])
			REP(k, 0, now[x])if(F[x][i][j][k]){
				renew(G[i][j + sz[v]][k], 1LL * F[x][i][j][k] * sub[v] % P * C(j + sz[v], sz[v]) % P);
				renew(G[i][j][k + sz[v]], 1LL * F[x][i][j][k] * sub[v] % P * C(k + sz[v], sz[v]) % P);
			}

			
			now[x] += sz[v];
			REP(i, 0, now[x])
			REP(j, 0, now[x])
			REP(k, 0, now[x]) F[x][i][j][k] = G[i][j][k];
		}
		
		int ned = (n - K) / 2;
		if(x == 1){
			renew(ans, F[x][K][ned][ned]);
			return;
		}
		
		REP(i, 0, sz[x])
		REP(j, 0, sz[x]) if(i == ned || j == ned){
			int ways = F[x][K][i][j];
			if(!ways) continue;
			if(i == ned){
				ways = 1LL * ways * ff[x] % P * C(j + n - sz[x], j) % P;
			}else{
				ways = 1LL * ways * ff[x] % P * C(i + n - sz[x], i) % P;
			}
			
			renew(ans, ways);
		}
	}
	
	int Main(){
		K = 2 * K - n;
		dfs(1);
		ff[1] = 1;
		dp1(1);
		dp2(1);
		REP(i, 1, K) ans = 1LL * ans * i % P;
		return ans;
	}
}

struct InducedSubgraphs{
	int getCount(VI edge1, VI edge2, int K){
		n = edge1.size() + 1;
		::K = K;
		if(K == 1){
			int ans = 1;
			REP(i, 1, n) ans = 1LL * ans * i % P;
			return ans;
		}
		fac[0] = invfac[0] = 1;
		REP(i, 1, n){
			fac[i] = 1LL * fac[i - 1] * i % P;
			invfac[i] = Pow(fac[i], P - 2, P);
		}
		FOR(i, 0, n - 1){
			int u = edge1[i] + 1;
			int v = edge2[i] + 1;
			e[u].pb(v);
			e[v].pb(u);
		}
		if(K * 2 <= n) return Work1 :: Main();
		return Work2 :: Main();
	}
}stu;