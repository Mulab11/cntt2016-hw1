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

int cnt;
char mps[N][N];
int X[N * N], Y[N * N];
int n, m, poi[N][N], ji, ou, ID[N][N];
int qx[N * N], qy[N * N], r, vis[N][N];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void bfs(){
	REP(i, 1, n) REP(j, 1, m) if(mps[i][j] == 'v'){
		++r;
		qx[r] = i;
		qy[r] = j;
		vis[i][j] = 1;
		poi[i][j] = ID[i][j];
	}
	REP(l, 1, r){
		int ux = qx[l], uy = qy[l];
		REP(d, 0, 3){
			int vx = ux + dx[d];
			int vy = uy + dy[d];
			if(vx < 1 || vx > n || vy < 1 || vy > m) continue;
			if(!vis[vx][vy]){
				poi[vx][vy] = poi[ux][uy];
				vis[vx][vy] = 1;
				qx[++r] = vx;
				qy[r] = vy;
			}
		}
	}
}

int fa[N * N], dist_lim;
int get(int x){
	if(fa[x] == x) return x;
	return fa[x] = get(fa[x]);
}

void try_merge(int u, int v){
	if(abs(X[u] - X[v]) + abs(Y[u] - Y[v]) > dist_lim) return;
	fa[get(u)] = get(v);
}

struct GooseInZooDivOne{
	int count(vector<string> field, int dist){
		n = field.size();
		m = field[0].size();
		dist_lim = dist;
		REP(i, 1, n) REP(j, 1, m) mps[i][j] = field[i - 1][j - 1];
		REP(i, 1, n) REP(j, 1, m) if(mps[i][j] == 'v'){
			ID[i][j] = ++cnt;
			X[cnt] = i;
			Y[cnt] = j;
		}
		
		bfs();
		
		REP(i, 1, cnt) fa[i] = i;
		REP(i, 1, n) REP(j, 1, m){
			REP(d, 0, 3){
				int x = i + dx[d];
				int y = j + dy[d];
				if(x < 1 || x > n || y < 1 || y > m) continue;
				try_merge(poi[x][y], poi[i][j]);
			}
		}
		
		static int SZ[N * N];
		memset(SZ, 0, sizeof SZ);
		REP(i, 1, cnt) SZ[get(i)] ++;
		REP(i, 1, cnt) if(SZ[i]){
			if(SZ[i] & 1) ji ++;
			else ou ++;
		}
		
		
		return (Pow(2, ou + max(ji - 1, 0), P) + P - 1) % P;
	}
}s;