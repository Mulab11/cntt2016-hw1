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

int fck[155];
int n, w[155][155], que[155], r;
int dfn[155], low[155], tim, stk[155], top, In[155];
int ban[155], V, e[155][155], mat[155], vis[155], ID[155];
struct Incubator{
	void tarjan(int x){
		dfn[x] = low[x] = ++tim;
		In[stk[++top] = x] = 1;
		REP(i, 1, n) if(w[x][i]){
			if(!dfn[i]){
				tarjan(i);
				chkmin(low[x], low[i]);
			}else if(In[i]) chkmin(low[x], dfn[i]);
		}
		if(low[x] == dfn[x]){
			int p = stk[top];
			int siz = 0;
			int fir = 0;
			do{
				p = stk[top];
				In[p] = 0;
				--top;
				++siz;
				fir = p;
			}while(p != x);
			if(siz == 1 && !w[fir][fir]) ban[fir] = 0;
		}
	}
	int find(int x){
		if(!x) return 1;
		REP(i, 1, V) if(e[x][i] && !vis[i]){
			vis[i] = 1;
			if(find(mat[i])){
				mat[i] = x;
				return 1;
			}
		}
		return 0;
	}
	int Match(){
		memset(mat, 0, sizeof mat);
		int res = V;
		REP(i, 1, V){
			memset(vis, 0, sizeof vis);
			res -= find(i);
		}
		return res;
	}
	int rt;
	void dfs(int x){
		if(vis[x]) return;
		vis[x] = 1;
		if(!ban[x] && ID[x] != rt) e[rt][ID[x]] = 1;
		REP(i, 1, n) if(w[x][i]) dfs(i);
	}
	int maxMagicalGirls(vector<string> love){
		n = love.size();
		REP(i, 1, n) REP(j, 1, n) if(love[i - 1][j - 1] == 'Y') w[j][i] = 1;
		REP(i, 1, n) ban[i] = 1;
		REP(i, 1, n) if(!dfn[i]) tarjan(i);
		REP(i, 1, n) if(!ban[i]) ID[i] = ++V;
		REP(i, 1, n)if(!ban[i]){
			memset(vis, 0, sizeof vis);
			rt = ID[i];
			dfs(i);
		}
		return Match();
	}
}stu;