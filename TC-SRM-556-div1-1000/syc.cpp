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
const	int N=105;
const	int M=10005;

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

int cnt, ID[N], n;
int r, que[N], dis[N];
struct edge{
	int v, w, pre;
};
struct maxflow{
	int s, t, dex, adj[N];
	edge e[M];
	void init(){
		dex = 1;
		memset(adj, 0, sizeof adj);
	}
	void adde(int x, int y, int z){
		e[++dex] = (edge){y, z, adj[x]}; adj[x] = dex;
		e[++dex] = (edge){x, 0, adj[y]}; adj[y] = dex;
	}
	int bfs(){
		REP(i, 1, cnt) dis[i] = -1;
		dis[que[r = 1] = s] = 0;
		REP(l, 1, r){
			int u = que[l];
			if(u == t) return 1;
			for(int i = adj[u]; i; i = e[i].pre){
				int v = e[i].v;
				if(e[i].w && dis[v] == -1) dis[que[++r] = v] = dis[u] + 1;
			}
		}
		return 0;
	}
	int dfs(int x, int f){
		if(x == t) return f;
		int ret = 0;
		for(int i = adj[x]; i; i = e[i].pre)if(e[i].w){
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
	int work(){
		int ans = 0;
		while(bfs()) ans += dfs(s, inf);
		return ans;
	}
}A,B;

struct OldBridges{
	string isPossible(vector<string> maps, int a1, int a2, int an, int b1, int b2, int bn){
		n = maps.size();
		REP(i, 1, n) ID[i] = ++cnt;
		A.init();
		B.init();
		A.s = B.s = ++cnt;
		A.t = B.t = ++cnt;
		a1 ++;
		a2 ++;
		b1 ++;
		b2 ++;
		an *= 2;
		bn *= 2;
		REP(i, 1, n) REP(j, 1, n){
			if(maps[i - 1][j - 1] == 'X') continue;
			if(maps[i - 1][j - 1] == 'N'){
				A.adde(ID[i], ID[j], inf);
				B.adde(ID[i], ID[j], inf);
			}else{
				A.adde(ID[i], ID[j], 2);
				B.adde(ID[i], ID[j], 2);
			}
		}
		A.adde(A.s, a1, an); A.adde(a2, A.t, an); A.adde(A.s, b1, bn); A.adde(b2, A.t, bn);
		B.adde(A.s, a1, an); B.adde(a2, A.t, an); B.adde(A.s, b2, bn); B.adde(b1, A.t, bn);
		if(A.work() >= an + bn && B.work() >= an + bn) return "Yes";
		return "No";
	}
}stu;