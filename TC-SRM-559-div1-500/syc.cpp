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
int fa[N];
int full[N], maxd[N], notv[N];
LL  dp[N];
VI adj[N];
VI son[N];
struct HatRack{
	LL dfs(int x){
		full[x] = 1;
		for(auto v : adj[x]){
			if(v == fa[x]) continue;
			fa[v] = x;
			son[x].pb(v);
			dfs(v);
			notv[x] |= notv[v];
			maxd[x] = max(maxd[x], maxd[v] + 1);
		}
		if(son[x].size() > 2 || notv[x]){
			full[x] = 0;
			notv[x] = 1;
			return 0;
		}
		if(son[x].size() == 0){
			dp[x] = 1;
			maxd[x] = 0;
			full[x] = 1;
			return dp[x];
		}
		if(son[x].size() == 1){
			if(maxd[son[x][0]] != 0){
				dp[x] = 0;
				return dp[x];
			}
			dp[x] = 1;
			full[x] = 0;
			return dp[x];
		}
		if(son[x].size() == 2){
			int u = son[x][0];
			int v = son[x][1];
			if(maxd[u] < maxd[v]) swap(u, v);
			if(maxd[u] != maxd[v]){
				if(maxd[u] - maxd[v] > 1){
					dp[x] = 0;
					return 0;
				}
				if(!full[v]){
					dp[x] = 0;
				}else{
					dp[x] += dp[u] * dp[v];
				}
			}else{
				if(full[u]){
					dp[x] += dp[u] * dp[v];
				}
				if(full[v]){
					dp[x] += dp[v] * dp[u];
				}
			}
			
			full[x] = full[u] & full[v];
			if(maxd[u] != maxd[v]) full[x] = 0;
		}
		return dp[x];
	}
	LL countWays(vector<int>knob1, vector<int>knob2){
		n = knob1.size() + 1;
		REP(i, 1, n - 1){
			adj[knob1[i - 1]].pb(knob2[i - 1]);
			adj[knob2[i - 1]].pb(knob1[i - 1]);
		}
		LL ans = 0;
		REP(i, 1, n){
			memset(fa, 0, sizeof fa);
			memset(dp, 0, sizeof dp);
			memset(notv, 0, sizeof notv);
			memset(full, 0, sizeof full);
			memset(maxd, 0, sizeof maxd);
			REP(j, 1, n) son[j].clear();
			ans += dfs(i);
		}
		return ans;
	}
}stu;