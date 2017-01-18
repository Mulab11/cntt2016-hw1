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
const	int P=1e9+7;
const	int N=55;

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

int n;
int ue[N], ve[N];
VI adj[N];

namespace KM{
	int n;
	int G[N][N], A[N], B[N], fl[N], fr[N];
	int F[N], visa[N], visb[N], pre[N], que[N], l, r;
	void init(int ver){
		n = ver;
		REP(i, 1, n) REP(j, 1, n) G[i][j] = 0;
		memset(A, 0, sizeof A);
		memset(B, 0, sizeof B);
		memset(fl, 0, sizeof fl);
		memset(fr, 0, sizeof fr);
	}
	void setw(int x, int y, int k){
		chkmax(G[x][y], k);
	}
	void Aug(int u){
		for(int v, w; u; ){
			v = pre[u];
			w = fl[v];
			fr[u] = v;
			fl[v] = u;
			u = w;
		}
	}
	void work(int x){
		REP(i, 1, n) F[i] = 1 << 20, visa[i] = visb[i] = pre[i] = 0;
		que[l = r = 1] = x;
		while(1){
			while(l <= r){
				int u = que[l]; l ++;	
				visa[u] = 1;
				REP(v, 1, n){
					if(visb[v]) continue;
					if(A[u] + B[v] == G[u][v]){
						pre[v] = u;
						if(!fr[v]){
							Aug(v);
							return;
						}else{
							visb[v] = 1;
							que[++r] = fr[v];
						}
					}else{
						if(A[u] + B[v] - G[u][v] < F[v]){
							pre[v] = u;
							F[v] = A[u] + B[v] - G[u][v];
						}
					}
				}
			}
			
			int d = 1 << 20;
			REP(i, 1, n) if(!visb[i]) d = min(d, F[i]);
			REP(i, 1, n) if(visa[i]) A[i] -= d;
			REP(i, 1, n) if(visb[i]) B[i] += d; else F[i] -= d;
			REP(i, 1, n) if(!visb[i] && !F[i]){
				if(!fr[i]){
					Aug(i);
					return;
				}else{
					visb[i] = 1;
					que[++r] = fr[i];
				}
			}
		}
	}
	int solve(){
		REP(i, 1, n) REP(j, 1, n) chkmax(A[i], G[i][j]);
		REP(i, 1, n) B[i] = 0, F[i] = 1 << 20;
		REP(i, 1, n) work(i);
		
		int ans = 0;
		REP(i, 1, n) ans += A[i] + B[i];
		return ans;
	}
};

int dp[N][N][N][N];

void dfs(int x, int y, VI &A){
	A.pb(x);
	for(auto v : adj[x]) if(v != y) dfs(v, x, A);
}

struct DeerInZooDivOne{
	
	int calc(int u, int fu, int v, int fv){
		if(dp[u][fu][v][fv] != -1) return dp[u][fu][v][fv];
		for(auto vt : adj[u]) if(vt != fu)
		for(auto wt : adj[v]) if(wt != fv) calc(vt, u, wt, v);
		
		int nl = 0, nr = 0;
		for(auto vt : adj[u]) nl ++;
		for(auto wt : adj[v]) nr ++;
		KM :: init(max(nl, nr));
		FOR(i, 0, adj[u].size())
		FOR(j, 0, adj[v].size()){
			if(adj[u][i] == fu || adj[v][j] == fv) continue;
			int val = dp[adj[u][i]][u][adj[v][j]][v];
			KM :: setw(i + 1, j + 1, val);
		}
		int val = KM :: solve();
		return dp[u][fu][v][fv] = 1 + val;
	}
	
	int getmax(VI a, VI b){
		n = a.size() + 1;
		memset(dp, -1, sizeof dp);
		REP(i, 1, n - 1){
			ue[i] = a[i - 1] + 1;
			ve[i] = b[i - 1] + 1;
		}
		int ans = 0;
		REP(bid, 1, n - 1){
			memset(dp, -1, sizeof dp);
			
			REP(i, 1, n) adj[i].clear(); 
			REP(j, 1, n - 1) if(j != bid){
				adj[ue[j]].pb(ve[j]);
				adj[ve[j]].pb(ue[j]);
			}
			
			VI A, B;
			dfs(ue[bid], 0, A);
			dfs(ve[bid], 0, B);
						
			for(auto u : A) for(auto v : B) chkmax(ans, calc(u, 0, v, 0));
		}
		return ans;
	}
}stu;