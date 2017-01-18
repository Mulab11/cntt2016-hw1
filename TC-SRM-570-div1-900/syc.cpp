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
const	int N=100005;

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

int n, m, cnt, S, T, id[26][26], po[26][26][5];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};
char mpt[26][26];
struct edge{
	int v, w, c, pre;
}e[1111111];
int dex = 1, adj[N], gtw;
int que[N], r, dis[N], pre[N], vis[N];

void adde(int x, int y, int w, int c){
	e[++dex] = (edge){y, w, c, adj[x]}; adj[x] = dex;
	e[++dex] = (edge){x, 0, -c, adj[y]}; adj[y] = dex;
}

class CurvyonRails{
public:
	int spfa(){
		REP(i, 1, cnt) dis[i] = inf, pre[i] = 0;
		dis[que[r = vis[S] = 1] = S] = 0;
		REP(l, 1, r){
			int u = que[l]; vis[u] = 0;
			for(int i = adj[u]; i; i = e[i].pre){
				int v = e[i].v;
				if(!e[i].w) continue;
				if(dis[u] + e[i].c < dis[v]){
					dis[v] = dis[u] + e[i].c;
					pre[v] = i;
					if(!vis[v]) vis[que[++r] = v] = 1;
				}
			}
		}
		return dis[T] != inf;
	}
	int mincost(){
		int ans = 0, fl = 0;
		while(spfa()){
			int aug = inf;
			for(int x = T; x ^ S; ){
				int pedge = pre[x];
				aug = min(aug, e[pedge].w);
				x = e[pedge ^ 1].v;
			}
			for(int x = T; x ^ S; ){
				int pedge = pre[x];
				e[pedge].w -= aug;
				e[pedge ^ 1].w += aug;
				x = e[pedge ^ 1].v;
			}
			ans += dis[T] * aug;
			fl += aug;
		}
		return fl == gtw ? ans : -1;
	}
	int getmin(vector<string> field){
		n = field.size();
		m = field[0].size();
		REP(i, 1, n) REP(j, 1, m) mpt[i][j] = field[i - 1][j - 1];
		S = ++cnt, T = ++cnt;
		REP(x, 1, n) REP(y, 1, m) REP(z, 0, 1) po[x][y][z] = ++cnt;
		REP(x, 1, n) REP(y, 1, m) id[x][y] = ++cnt;
		REP(x, 1, n) REP(y, 1, m){
			if(mpt[x][y] == 'w') continue;
			if((x + y) & 1){
				adde(S, id[x][y], 2, 0);
				adde(id[x][y], po[x][y][0], 1, 0);
				adde(id[x][y], po[x][y][1], 1, 0);
				FOR(k, 0, 4){
					int u = x + dx[k], v = y + dy[k];
					if(u <= 0 || u > n || v <= 0 || v > m) continue;
					if(mpt[u][v] == 'w') continue;
					
					adde(po[x][y][k & 1], po[u][v][k & 1], 1, 0);
				}
			}else{
				adde(po[x][y][0], id[x][y], 1, 0);
				adde(po[x][y][1], id[x][y], 1, 0);
				adde(id[x][y], T, 2, 0);
			}
			
			adde(po[x][y][0], po[x][y][1], 1, mpt[x][y] == 'C');
			adde(po[x][y][1], po[x][y][0], 1, mpt[x][y] == 'C');
			++gtw;
		}
		
		return mincost();
	}
} stu;