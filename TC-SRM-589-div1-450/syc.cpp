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
const	int N=55	;

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

int n, colx, coly;
int col[N], mat[N], vis[N];
bool adj[N][N];
bool e[N][N], c[5][5];

struct GearsDiv1{
	
	int trans(char w){
		if(w == 'R') return 1;
		if(w == 'G') return 2;
		return 3;
	}
	
	int find(int x){
		if(!x) return 1;
		REP(i, 1, n) if(!vis[i] && adj[x][i]){
			vis[i] = 1;
			if(find(mat[i])){
				mat[i] = x;
				return 1;
			}
		}
		return 0;
	}
	
	int work(int x, int y){
		colx = x;
		coly = y;
		memset(mat, 0, sizeof mat);
		memset(adj, 0, sizeof adj);
		REP(i, 1, n) if(col[i] == colx)
		REP(j, 1, n) if(col[j] == coly && e[i][j]) adj[i][j] = 1;
		int ans = 0;
		REP(i, 1, n){
			memset(vis, 0, sizeof vis);
			ans += find(i);
		}
		return ans;
	}
	
	int getmin(string color, vector<string> graph){
		n = color.size();
		REP(i, 1, n) col[i] = trans(color[i - 1]);
		REP(i, 1, n) REP(j, 1, n) e[i][j] = graph[i - 1][j - 1] == 'Y';
		REP(i, 1, n) REP(j, 1, n) if(e[i][j]) c[col[i]][col[j]] = 1;
		if(!c[1][2] || !c[2][3] || !c[1][3]) return 0;
		int res = 1 << 30;
		chkmin(res, work(1, 2));
		chkmin(res, work(1, 3));
		chkmin(res, work(2, 3));
		return res;
	}
};