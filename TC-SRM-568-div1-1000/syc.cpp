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
typedef long long ll;
typedef PR<int,int> PII;
const	int inf=2e9;
const	ll Inf=1e10;
const	int P=1e9+7;
const	int N=66;

inline int IN(){
	int x = 0, ch = 0, f = 0;
	for (CH; ch != -1 && (ch < 48 || ch > 57); CH) f = (ch == '-');
	for (; ch >= 48 && ch <= 57; CH) x = (x << 1) + (x << 3) + ch - '0';
	return f ? (-x) : x;
}

int Pow(int x, int y, int p){
	int a = 1;
	for (; y; y >>= 1, x = (ll)x * x %p) if(y & 1) a=(ll)a * x%p;
	return a;
}

int a[N], n, m, par[N], op[N], sm[N];
vector<PII> e[N];

void ade(int u, int v, int w){
	e[u].pb(mk(v, w));
	e[v].pb(mk(u, w));
}

void dfsc(int x, int c){
	if(par[x] != -1) return;
	par[x] = c;
	FOR(i, 0, e[x].size()) dfsc(e[x][i].fi, c ^ e[x][i].se);
}

namespace task1{
	int col[N];
	int chk(){
		FOR(i, 0, n) e[i].clear();
		memset(par, -1, sizeof par);
		REP(i, 1, m) REP(j, i + 1, m) if(a[j] == a[i]){
			REP(x, 1, m) if(x != i) REP(y, x + 1, m) if(a[x] == a[y]){
				if((i < x && x < j && j < y) || (x < i && i < y && y < j)){
					ade(a[i], a[x], 1);
				}
			}
		}
		
		FOR(i, 0, n) if(par[i] == -1) dfsc(i, 0);
		FOR(i, 0, n) FOR(j, 0, e[i].size()) if((par[i] ^ par[e[i][j].fi]) != e[i][j].se) return 0;
		return 1;
	}
	int dfs(int x){
		if(x > m) return chk();
		if(a[x] != -1) return dfs(x + 1);
		int u1 = 0;
		FOR(i, 0, n){
			if(col[i] == 2 || col[i] < u1)continue;
			col[i]++; a[x] = i;
			if(dfs(x + 1)) return 1;
			col[i]--; a[x] = -1;
			if(!col[i]) u1 = 1;
		}
		return 0;
	}
	string work(){
		REP(i, 1, m) if(a[i] != -1) col[a[i]] ++;
		return dfs(1) ? "POSSIBLE" : "IMPOSSIBLE";
	}
}

namespace task2{
	int sm[N], f[N];
	vector<int> V[N];
	int chk(){
		REP(i, 0, m) e[i].clear();
		memset(par, -1, sizeof par);
		FOR(i, 0, m) if(a[i + 1] >= 0) ade(i, i + 1, 0);
		ade(0, m, 0);
		
		REP(i, 1, m) if(a[i] >= 0 && i < op[i]){
			if(f[i]) ade(i - 1, op[i] - 1, 0);
			else ade(i - 1, op[i] - 1, (sm[op[i]] - sm[i]) & 1);
		}
		
		REP(i, 0, m) if(par[i] == -1) dfsc(i, 0);
		REP(i, 0, m) FOR(j, 0, e[i].size()) if((par[i] ^ par[e[i][j].fi]) != e[i][j].se) return 0;
		return 1;
	}
	int dfs(int x){
		if(x > m) return chk();
		if(a[x] == -1 || x > op[x]) return dfs(x + 1);
		REP(i, 0, 1){
			f[x] = f[op[x]] = i;
			int valid = 1;
			FOR(j, 0, V[x].size()) if(f[V[x][j]] >= -1 && f[V[x][j]] == i) valid = 0;
			if(valid && dfs(x + 1)) return 1;
			f[x] = f[op[x]] = -1;
		}
		return 0;
	}
	string work(){
		REP(i, 1, m) sm[i] = sm[i - 1] + (a[i] == -1);
		REP(i, 1, m) REP(j, 1, m){
			if(a[i] == -1 || a[j] == -1) continue;
			if(i > op[i] || j > op[j]) continue;
			if((j < op[i] && i < j && op[j] > op[i]) || (j < i && i < op[j] && op[j] < op[i]))
				V[i].pb(j);
		}
		memset(f, -1, sizeof f);
		return dfs(1) ? "POSSIBLE" : "IMPOSSIBLE";
	}
}

struct DisjointSemicircles{
	string getPossibility(vector<int> lables){
		n = lables.size() / 2;
		m = n << 1;
		REP(i, 1, m) a[i] = lables[i - 1];
		REP(i, 1, m){
			if(a[i] == -1) continue;
			REP(j, i + 1, m){
				if(a[j] ^ a[i]) continue;
				op[i] = j;
				op[j] = i;
			}
		}
		int cnt = 0;
		REP(i, 1, m) if(a[i] == -1) cnt++;
		return (cnt <= 12) ? task1::work() : task2::work();
	}
} stu;