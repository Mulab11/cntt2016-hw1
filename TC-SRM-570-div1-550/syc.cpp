#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <bitset>
#include <vector>
#include <string>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define REP(i, x, y)  for(int i = (int)x; i <= (int)y; i ++)
#define FOR(i, x, y)  for(int i = (int)x; i <  (int)y; i ++)
#define PER(i, x, y)  for(int i = (int)x; i >= (int)y; i --)
#define fi first
#define se second
#define pb push_back
#define mk make_pair
using namespace std;
typedef double db;
typedef long long ll;
typedef long long LL;
typedef pair<int, int> PII;
const	int N = 55;
const	int inf = 1e9;
const	ll Inf = 1e16;
const	int P = 998244353;

bool st;
int n;
vector<int> adj[N];
LL DP[N][2 * N][2];
int fa[N], sz[N];
LL g1[N * 2], g2[N * 2], g3[N * 2], g4[N * 2];
bool en;

void chk(LL &u, LL v){
	u += v;
}

void DFS(int x){
	FOR(i, 0, adj[x].size()){
		int v = adj[x][i];
		if(v == fa[x]) continue;
		fa[v] = x;
		DFS(v);
	}
	
	memset(g1, 0, sizeof g1);
	memset(g2, 0, sizeof g2);
	memset(g3, 0, sizeof g3);
	memset(g4, 0, sizeof g4);
	
	g1[n] = g3[n] = 1;
	FOR(i, 0, adj[x].size()){
		int v = adj[x][i];
		if(v == fa[x]) continue;
		fa[v] = x;
		
		memcpy(g4, g3, sizeof g4);
		memset(g3, 0, sizeof g3);
		memcpy(g2, g1, sizeof g2);
		memset(g1, 0, sizeof g1);
		
		REP(x1, -sz[v], sz[v]){
			LL val = DP[v][x1 + n][0] + DP[v][x1 + n][1];
			if(!val) continue;
			REP(x0, -sz[x], sz[x]){
				chk(g3[x0 + x1 + n], g4[x0 + n] * val);
			}
		}
		
		REP(x1, -sz[v], sz[v])
		REP(st, 0, 1){
			LL val = DP[v][x1 + n][st];
			if(!val) continue;
			REP(y, -sz[x], sz[x]){
				int nw = y + x1;
				if(st) nw -= 2;
//				assert(-n <= nw && nw <= n);
				chk(g1[nw + n], g2[y + n] * val);
			}
		}
		
		sz[x] += sz[v];
	}
	
	++ sz[x];
	REP(i, -sz[x], sz[x]) chk(DP[x][i + n][0], g3[i + n]);
	REP(i, -sz[x], sz[x]) chk(DP[x][i + n + 1][1], g1[i + n]);
	
}


struct CentaurCompany{
	double getvalue(vector<int> a, vector<int> b){
		n = a.size() + 1;
		FOR(i, 0, a.size()){
			int x = a[i];
			int y = b[i];
			adj[x].pb(y);
			adj[y].pb(x);
		}
		
		DFS(1);
		LL ans = 0;
		REP(i, -n, n) REP(j, 0, 1){
			int tot = max(0, i - 2);
			if(!tot) continue;
			LL val = DP[1][i + n][j] * tot;
			chk(ans, val);
		}
		
		chk(ans, ans);
		
		cout << ans << endl;
		
		double res = ans;
		REP(i, 1, n) res *= 0.5;
		return res;
	}
}stu;