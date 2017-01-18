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

int n, p, st[N], en[N], du[N], f[N][N];
int dp[1 << 16][16];
struct TravellingPurchasingMan{
	int work(int x, int tim){
		if(tim < st[x]) return st[x] + du[x];
		if(tim > en[x]) return inf;
		return tim + du[x];
	}
	int maxStores(int S, vector<string> inter, vector<string> roads){
		n = S;
		p = 0;
		for(string w : inter){
			sscanf(w.c_str(), "%d%d%d", st + p, en + p, du + p);
			p ++;
		}
		memset(f, 0x3f, sizeof f);
		FOR(i, 0, n) f[i][i] = 0;
		for(string w : roads){
			int u, v, c;
			sscanf(w.c_str(), "%d%d%d", &u, &v, &c);
			chkmin(f[u][v], c);
			chkmin(f[v][u], c);
		}
		
		//预处理最短路。
		FOR(k, 0, n) FOR(i, 0, n) FOR(j, 0, n) chkmin(f[i][j], f[i][k] + f[k][j]);
		
		//直接状压dp即可.
		//用f[S][i]表示当前经过了集合S中的点,最后一个经过的是i.
		//枚举一个j转移即可.
		memset(dp, 0x3f, sizeof dp);
		FOR(k, 0, p) dp[1 << k][k] = work(k, f[n - 1][k]);
		FOR(s, 1, 1 << p) FOR(j, 0, p) if(dp[s][j] < 1e9){
			FOR(k, 0, p) if(!((s >> k) & 1)) chkmin(dp[s | (1 << k)][k], work(k, dp[s][j] + f[j][k]));
		}
		
		int res = 0;
		FOR(s, 1, 1 << p){
			int cnt = 0;
			FOR(j, 0, p) if((s >> j) & 1) ++cnt;
			FOR(j, 0, p) if(dp[s][j] < 1e9) chkmax(res, cnt);
		}
		return res;
	}
}s;