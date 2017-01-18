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

int vis[N];
int n, cnt, ans;
int fa[N], ID[N];
VI e[N];
int get(int x){
	if(fa[x] == x) return x;
	return fa[x] = get(fa[x]);
}
struct TurnOnLamps{
	
	void dfs(int x, int y){
		vis[x] = 1;
		int son = 0;
		for(auto w : e[x]){
			if(vis[w]) continue;
			++son;
			dfs(w, x);
		}
		if(y) ans += son / 2;
		else ans += (son + 1) / 2;
	}
	
	int minimize(VI roads, string init, string last){
		n = init.length() + 1;
		REP(i, 1, n) fa[i] = i;
		REP(i, 2, n){
			int u = roads[i - 2] + 1;
			if(last[i - 2] == '0') fa[get(i)] = get(u);
		}
		REP(i, 1, n) if(get(i) == i) ID[i] = ++cnt;
		REP(i, 2, n){
			int u = ID[get(roads[i - 2] + 1)];
			int v = ID[get(i)];
			if(last[i - 2] == '1' && init[i - 2] == '0'){
				e[u].pb(v);
				e[v].pb(u);
			}
		}
		REP(i, 1, cnt) if(!vis[i]) dfs(i, 0);
		return ans;
	}
}s;