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
const	int N=100005;

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

bool nosol = 0;
int m1, m2, n;
int u1[N], v1[N], l1[N];
int u2[N], v2[N], l2[N];
vector<pair<int, pair<LL, int> > > adj[N];
pair<LL, int> dis[N];

struct YamanoteLine{
	int check(LL key){
		//return 0 : it is valid
		//return 1 : it need to be bigger
		//return -1: it need to be smaller
		//there is an edge from adj[i][x].first to i with adj[i].second length
		//D[i] <= D[i + 1] - 1
		//D[n] <= D[1] + key
		//D[1] <= D[n] - key
		REP(i, 1, n + 1) adj[i].clear();
		REP(i, 1, n) adj[i].pb(mk(i + 1, mk(-1, 0)));
		adj[n + 1].pb(mk(1, mk(key, 1)));
		adj[1].pb(mk(n + 1, mk(-key, -1)));
		
		REP(i, 1, m1){
			int u = u1[i];
			int v = v1[i];
			int w = l1[i];
			if(u < v){
				//D[u] <= D[v] - w
				adj[u].pb(mk(v, mk(-w, 0)));
			}else{
				//D[u] <= key + D[v] - w
				adj[u].pb(mk(v, mk(key - w, 1)));
			}
		}
		
		REP(i, 1, m2){
			int u = u2[i];
			int v = v2[i];
			int w = l2[i];
			if(u < v){
				//D[v] <= D[u] + w
				adj[v].pb(mk(u, mk(w, 0)));
			}else{
				//D[v] <= D[u] + w - key
				adj[v].pb(mk(u, mk(w - key, -1)));
			}
		}
		
		REP(i, 1, n + 1) dis[i] = mk(1e11, 0);
		dis[1] = mk(0, 0);
		pair<LL, int> dd, gt;
		
		bool up = 0;
		REP(lp, 1, (n + 1) * (n + 1)){
			up = 0;
			REP(i, 1, n + 1){
				for(auto v : adj[i]){
					int fr = v.fi;
					LL w1 = v.se.fi + dis[fr].fi;
					int w2 = v.se.se + dis[fr].se;
					dd = mk(w1, w2);
					if(dd.fi < dis[i].fi){
						up = 1;
						dis[i] = dd;
						gt = dd;
						if(dd.fi < 0){
							if(dd.se > 0){
								//x * key + y < 0, x > 0
								//key need to be bigger
								return 1;
							}
							if(dd.se == 0){
								//x * key + y < 0, x = 0
								//no solution
								nosol = 1;
								return 1;
							}
							if(dd.se < 0) return -1;
						}
					}
				}
			}
		}
		
		if(!up) return 0;
		if(gt.se == 0){
			nosol = 1;
			return 1;
		}
		if(gt.se > 0) return 1;
		if(gt.se < 0) return -1;
		
		return -1;
	}
	
	LL Main(){
		LL l, r, ub, lb;
		//找到length的上界
		l = n, r = 1e11, ub = 1e11;
		while(l <= r){
			LL md = (l + r) / 2;
			int st = check(md);
			if(nosol) return 0;
			if(st == 0){
				ub = md;
				l = md + 1;
			}
			if(st == 1){
				l = md + 1;
			}
			if(st == -1){
				r = md - 1;
			}
		}
		//找到length的下界
		l = n, r = 1e11, lb = -1;
		while(l <= r){
			LL md = (l + r) / 2;
			int st = check(md);
			if(nosol)return 0;
			if(st == 0){
				lb = md;
				r = md - 1;
			}
			if(st == 1){
				l = md + 1;
			}
			if(st == -1) r = md - 1;
		}
		
		
		if(lb >= n && ub == 1e11) return -1;
		if(lb == -1 || nosol) return 0;
		return max(0LL, ub - lb + 1);
		
	}
	LL howMany(int n, VI s1, VI t1, VI l1, VI s2, VI t2, VI l2){
		m1 = s1.size();
		m2 = s2.size();
		::n = n;
		REP(i, 1, m1){
			::u1[i] = s1[i - 1] + 1;
			::v1[i] = t1[i - 1] + 1;
			::l1[i] = l1[i - 1];
		}
		REP(i, 1, m2){
			::u2[i] = s2[i - 1] + 1;
			::v2[i] = t2[i - 1] + 1;
			::l2[i] = l2[i - 1];
		}
		return Main();
	}
}stu;