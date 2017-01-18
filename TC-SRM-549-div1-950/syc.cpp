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
const	int N=35;

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

int cnt, ver;
int n, L, R, col[N];
VI lev[N];
int ID1[N], ID2[N], S, T, s, t;
int ee[N], vis[N], In[N], Ou[N];
int F[1 << 7];
int adj[155], dex = 0;
struct edge{
	int v, w, pre;
}e[100000];

int que[10005], r, dis[10005];
struct CosmicBlocks{
	
	int bfs(int S, int T){
		REP(i, 1, ver) dis[i] = -1;
		dis[que[r = 1] = S] = 0;
		REP(l, 1, r){
			int u = que[l];
			if(u == T) return 1;
			for(int i = adj[u]; i; i = e[i].pre){
				if(!e[i].w)continue;
				int v = e[i].v;
				if(dis[v] < 0) dis[que[++r] = v] = dis[u] + 1;
			}
		}
		return 0;
	}
	
	int dfs(int x, int T, int f){
		if(x == T) return f;
		int ret = 0;
		for(int i = adj[x]; i; i = e[i].pre){
			int v = e[i].v;
			if(!e[i].w || dis[v] != dis[x] + 1) continue;
			int F = dfs(v, T, min(f - ret, e[i].w));
			e[i].w -= F;
			e[i ^ 1].w += F;
			ret += F;
			if(ret == f) return ret;
		}
		if(!ret) dis[x] = -1;
		return ret;
	}
	
	int Flow(int S, int T){
		int ans = 0;
		while(bfs(S, T)) ans += dfs(S, T, inf);
		return ans;
	}
	
	void add(int x, int y, int l, int r){
		In[y] += l;
		Ou[x] += l;
		r -= l;
		if(r){
			e[++dex] = (edge){y, r, adj[x]}; adj[x] = dex;
			e[++dex] = (edge){x, 0, adj[y]}; adj[y] = dex;
		}
	}
		
	int check(){
		REP(i, 1, ver) In[i] = Ou[i] = 0;
		REP(i, 1, ver) adj[i] = 0; dex = 1;
		int sum = 0;
		REP(i, 1, n) sum += col[i];
		REP(i, 1, n) add(S, ID1[i], 0, col[i]);
		REP(i, 1, n) add(ID2[i], T, 0, col[i]);
		for(auto v : lev[1]) add(ID1[v], T, 0, inf);
		REP(i, 1, n)
		REP(j, 1, n) if((ee[i] >> j) & 1){
			add(ID1[j], ID2[i], 1, inf);
		}
		
		REP(i, 1, ver) if(In[i]) add(s, i, 0, In[i]);
		REP(i, 1, ver) if(Ou[i]) add(i, t, 0, Ou[i]);
		add(T, S, 0, inf);
		
		Flow(s, t);
		for(int i = adj[s]; i; i = e[i].pre) if(e[i].w) return 0;
		return Flow(S, T) == sum;
	}
	int dp(int s){
		if(s + 1 == (1 << n)) return 1;
		int &res = F[s];
		if(res != -1) return res;
		res = 0;
		FOR(i, 0, n){
			if(!((s >> i) & 1)){
				if((ee[i + 1] & (s << 1)) == (ee[i + 1])){
					res += dp(s | (1 << i));
				}
			}
		}
		return res;
	}
	int calc(){
		memset(F, -1, sizeof F);
		return dp(0);
	}
	void DFS(int stp, int h, int prev){
		if(stp > n){
			if(lev[h].size()){
				if(check()){
					int ways = calc();
					if(L <= ways && ways <= R) cnt++;
				}
			}
			return;
		}
		REP(i, prev + 1, n)if(!vis[i]){
			vis[i] = 1;
			lev[h].pb(i);
			if(h == 1){
				DFS(stp + 1, h, i);
				DFS(stp + 1, h + 1, -1);
			}else{
				int SZ = lev[h - 1].size();
				FOR(j, 1, 1 << SZ){
					FOR(k, 0, SZ){
						int v = lev[h - 1][k];
						if((j >> k) & 1) ee[v] ^= 1 << i;
					}
					DFS(stp + 1, h, i);
					DFS(stp + 1, h + 1, -1);
					FOR(k, 0, SZ){
						int v = lev[h - 1][k];
						if((j >> k) & 1) ee[v] ^= 1 << i;
					}
				}
			}
			vis[i] = 0;
			lev[h].pop_back();
		}
	}
	int getNumOrders(VI blockTypes, int minWays, int maxWays){
		n = blockTypes.size();
		REP(i, 1, n) col[i] = blockTypes[i - 1];
		L = minWays;
		R = maxWays;
		
		REP(i, 1, n) ID1[i] = ++ver, ID2[i] = ++ver;
		S = ++ver, T = ++ver, s = ++ver, t = ++ver;
		
		DFS(1, 1, 0);
		
		return cnt;
	}
} stu;