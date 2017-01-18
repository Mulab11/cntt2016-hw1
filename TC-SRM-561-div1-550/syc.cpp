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

int tim;
int n, fa[N], sg[N], vis[N];
VI adj[N], sub[N];

int sqr(int x){
	return x * x;
}

struct CirclesGame{
	int dfs(int x){
		for(int v : adj[x]) dfs(v);
		++tim;
		for(int v : sub[x]){
			int pre = 0, res = 0;
			for(int w = v; w; w = fa[w]){
				for(int t : adj[w]){
					if(t == pre) continue;
					res ^= sg[t];
				}
				pre = w;
				if(w == x) break;
			}
			vis[res] = tim;
		}
		int &g = sg[x];
		g = 0;
		while(vis[g] == tim) ++g;
		return g;
	}
	string whoCanWin(VI x, VI y, VI r){
		n = x.size();
		REP(i, 1, n)
		REP(j, 1, n)if(r[i - 1] > r[j - 1]){
			int dis = sqr(x[i - 1] - x[j - 1]) + sqr(y[i - 1] - y[j - 1]);
			if(dis < (r[i - 1] - r[j - 1]) * (r[i - 1] - r[j - 1])){
				if(!fa[j] || r[i - 1] < r[fa[j] - 1]) fa[j] = i;
				sub[i].pb(j);
			}
		}
		
		REP(i, 1, n) sub[i].pb(i);
		
		REP(i, 1, n) adj[fa[i]].pb(i);
		int ans = 0;
		REP(i, 1, n) if(!fa[i]) ans ^= dfs(i);
		if(ans) return "Alice"; else return "Bob";
	}
}stu;