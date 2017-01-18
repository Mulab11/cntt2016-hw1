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

int n, m, cnt, A[25][25], B[25][25], ans, S, T;
struct edge{
	int v, w, pre;
}e[1000005]; int dex = 1, adj[1055];

void add(int x, int y, int z){
	e[++dex] = (edge){y, z, adj[x]}; adj[x] = dex;
	e[++dex] = (edge){x, 0, adj[y]}; adj[y] = dex;
}

int dis[1055], que[1055], r;
int bfs(){
	REP(i, 1, cnt) dis[i] = -1;
	dis[que[r = 1] = S] = 0;
	REP(l, 1, r){
		int u = que[l];
		if(u == T) return 1;
		for(int i = adj[u]; i; i = e[i].pre) if(e[i].w){
			int v = e[i].v;
			if(dis[v] == -1) dis[que[++r] = v] = dis[u] + 1;
		}
	}
	return 0;
}

int dfs(int x, int f){
	if(x == T) return f;
	int ret = 0;
	for(int i = adj[x]; i; i = e[i].pre) if(e[i].w){
		int v = e[i].v;
		if(dis[v] != dis[x] + 1) continue;
		int F = dfs(v, min(f - ret, e[i].w));
		e[i].w -= F;
		e[i ^ 1].w += F;
		ret += F;
		if(ret == f) return ret;
	}
	if(!ret) dis[x] = -1;
	return ret;
}

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct SurroundingGame{
	int Val(char x){
		if('0' <= x && x <= '9') return x - '0';
		if('a' <= x && x <= 'z') return x - 'a' + 10;
		if('A' <= x && x <= 'Z') return x - 'A' + 36;
	}
	int maxScore(vector<string> cost, vector<string> benefit){
		n = cost.size();
		m = cost[0].size();
		FOR(i, 0, n) FOR(j, 0, m) A[i][j] = ++cnt, B[i][j] = ++cnt;
		S = ++cnt;
		T = ++cnt;
		FOR(i, 0, n) FOR(j, 0, m) ans += Val(benefit[i][j]);
		FOR(i, 0, n) FOR(j, 0, m){
			int v = Val(benefit[i][j]);
			int c = Val(cost[i][j]);
			if((i + j) % 2 == 0){
				REP(k, 0, 3){
					int xx = i + dx[k];
					int yy = j + dy[k];
					if(xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
					add(B[i][j], A[xx][yy], inf);
				}
				add(A[i][j], B[i][j], v);
				add(S, A[i][j], c);
			}else{
				REP(k, 0, 3){
					int xx = i + dx[k];
					int yy = j + dy[k];
					if(xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
					add(A[xx][yy], B[i][j], inf);
				}
				add(B[i][j], A[i][j], v);
				add(A[i][j], T, c);
			}
		}
		while(bfs()) ans -= dfs(S, inf);
		return ans;
	}
};