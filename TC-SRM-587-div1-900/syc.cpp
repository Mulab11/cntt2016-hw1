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


int n, m;
int ID[N][N], cnt;
char mps[N][N];
int X[N << 1];
VPI e[N << 1];
struct ThreeColorability{
	
	#define trans(w) ((w) == 'Z')
	
	int dfs(int x, int y){
//		printf("%d %d\n", x, y);
		if(X[x] == -1){
			X[x] = y;
		}else{
			if(X[x] != y) return 0;
			return 1;
		}
		for(auto w : e[x]) if(!dfs(w.fi, y ^ w.se)) return 0;
		return 1;
	}
	
	int check(){
		if(min(n, m) == 1) return 1;
		memset(X, -1, sizeof X);
		REP(i, 0, cnt) e[i].clear();
		FOR(i, 1, n) FOR(j, 1, m)if(mps[i][j] != '?'){
			int c = trans(mps[i][j]);
			int u = 0, v = 0;
			if(mps[0][j] == '?') u = ID[0][j]; else c ^= trans(mps[0][j]);
			if(mps[i][0] == '?') v = ID[i][0]; else c ^= trans(mps[i][0]);
			c ^= trans(mps[0][0]);
			if(!u && !v){
				if(c) return 0;
			}else
			if(u && !v){
				e[0].pb(mk(u, c));
				e[u].pb(mk(0, c));
			}else
			if(v && !u){
				e[0].pb(mk(v, c));
				e[v].pb(mk(0, c));
			}else{
				e[u].pb(mk(v, c));
				e[v].pb(mk(u, c));
			}
		}
	
		REP(i, 0, cnt)
			if(X[i] == -1) if(!dfs(i, 0)) return 0;
		return 1;
	}
	
	vector<string> lexSmallest(vector<string> cells){
		n = cells.size();
		m = cells[0].size();
		FOR(i, 0, n) FOR(j, 0, m) mps[i][j] = cells[i][j];
		if(n > 1 && m > 1){
			FOR(i, 0, m) ID[0][i] = ++cnt;
			FOR(i, 1, n) ID[i][0] = ++cnt;
		}
		if(mps[0][0] != '?'){
			if(!check()) return vector<string>();
		}
		FOR(i, 0, n) FOR(j, 0, m){
			if(mps[i][j] != '?') continue;
			mps[i][j] = 'N';
			if(!check()){
				mps[i][j] = 'Z';
				if(!check()) return vector<string>();
			}
		}
		vector<string> res;
		FOR(i, 0, n){
			string t;
			FOR(j, 0, m) t.pb(mps[i][j]);
			res.pb(t);
		}
		return res;
	}
}s;