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

char mps[N][N];
int n, m, S, T;
int ID1[N][N], ID2[N][N], cnt;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int dex = 1;
struct edge{
	int v, w, pre;
}e[1000000]; int adj[100005];

void add(int x, int y, int z){
	e[++dex] = (edge){y, z, adj[x]}; adj[x] = dex;
	e[++dex] = (edge){x, 0, adj[y]}; adj[y] = dex;
}

struct TheTilesDivOne{
	int valid(int x, int y){
		if(x < 0 || x >= n || y < 0 || y >= m) return 0;
		if(mps[x][y] == 'X') return 0;
		return 1;
	}
	
	int dis[100005], r, que[100005];
	int BFS(int S, int T){
		REP(i, 1, cnt) dis[i] = -1;
		dis[que[r = 1] = S] = 0;
		REP(l, 1, r){
			int u = que[l];
			if(u == T) return 1;
			for(int i = adj[u]; i; i = e[i].pre)if(e[i].w){
				int v = e[i].v;
				if(dis[v] == -1) dis[que[++r] = v] = dis[u] + 1;
			}
		}
		return 0;
	}
	
	int DFS(int x, int f){
		int ret = 0;
		if(x == T) return f;
		for(int i = adj[x]; i; i = e[i].pre)if(e[i].w){
			int v = e[i].v;
			if(dis[v] != dis[x] + 1) continue;
			int F = DFS(v, min(f - ret, e[i].w));
			e[i].w -= F;
			e[i ^ 1].w += F;
			ret += F;
			if(ret == f) return ret;
		}
		if(!ret) dis[x] = -1;
		return ret;
	}
	
	int Main(){
		int ans = 0;
		while(BFS(S, T)) ans += DFS(S, 1 << 30);
		return ans;
	}
	
	int find(vector<string> board){
		cnt = 0;
		n = board.size();
		m = board[0].size();
		S = ++cnt;
		T = ++cnt;
		FOR(i, 0, n) FOR(j, 0, m){
			mps[i][j] = board[i][j];
			ID1[i][j] = ++cnt;
			if((i + j) % 2 == 0) ID2[i][j] = ++cnt;
		}
		FOR(i, 0, n) FOR(j, 0, m){
			if(mps[i][j] == 'X') continue;
			if((i + j) % 2 == 0){
				add(ID1[i][j], ID2[i][j], 1);
				FOR(d, 0, 4){
					int x = i + dx[d];
					int y = j + dy[d];
					if(!valid(x, y) || x % 2 == 0) continue;
					add(ID2[i][j], ID1[x][y], inf);
				}
			}else{
				if(!(i & 1)){
					add(S, ID1[i][j], 1);
					FOR(d, 0, 4){
						int x = i + dx[d];
						int y = j + dy[d];
						if(!valid(x, y)) continue;
						add(ID1[i][j], ID1[x][y], inf);
					}
				}else{
					add(ID1[i][j], T, 1);
				}
			}
		}
		
		return Main();
	}
}s;