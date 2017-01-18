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

int n, m, cnt, S, T, ID[N][N];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int dex = 1, adj[100005];
int que[100005], dis[100005], r;
struct edge{
	int v, w, pre;
}e[1000005];

struct FoxAndGo3{

	int bfs(int S, int T){
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

	int dfs(int x, int f){
		if(x == T) return f;
		int ret = 0;
		for(int i = adj[x]; i; i = e[i].pre) if(e[i].w) {
			int v = e[i].v;
			if(dis[v] == dis[x] + 1){
				int F = dfs(v, min(f - ret, e[i].w));
				e[i].w -= F;
				e[i ^ 1].w += F;
				ret += F;
				if(ret == f) return ret;
			}
		}
		if(!ret) dis[x] = -1;
		return ret;
	}

	void add(int x, int y, int w){
		e[++dex] = (edge){y, w, adj[x]}; adj[x] = dex;
		e[++dex] = (edge){x, 0, adj[y]}; adj[y] = dex;
	}

	int maxEmptyCells(vector<string> board){
		n = board.size();
		m = board[0].size();
		S = ++cnt;
		T = ++cnt;
		int ans = 0;
		FOR(i, 0, n) FOR(j, 0, m) ID[i][j] = ++cnt;
		FOR(i, 0, n) FOR(j, 0, m){
			if(board[i][j] == 'o'){
				add(S, ID[i][j], 1);
				FOR(k, 0, 4){
					int nx = i + dx[k];
					int ny = j + dy[k];
					if(nx < 0 || nx >= n || ny < 0 || ny >= m || board[nx][ny] == 'x') continue;
					add(ID[i][j], ID[nx][ny], inf);
				}
				++ans;
			}else
			if(board[i][j] == '.'){
				add(ID[i][j], T, 1);
				++ ans;
			}
		}
		while(bfs(S, T)) ans -= dfs(S, inf);
		return ans;
	}
}s;