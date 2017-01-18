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

int n, m;
int X1[55], X2[55], Y1[55], Y2[55], cnt;
LL F[1 << 9];

void add(int xl, int xr, int yl, int yr){
	if(xl > xr) return;
	if(yl > yr) return;
	++cnt;
	X1[cnt] = xl;
	X2[cnt] = xr;
	Y1[cnt] = yl;
	Y2[cnt] = yr;
}

void dfs(int x, int y, int xl, int xr, int yl, int yr){
	if(x > cnt){
		F[y] = 1LL * max(0, xr - xl + 1) * max(0, yr - yl + 1);
		return;
	}
	dfs(x + 1, y, xl, xr, yl, yr);
	dfs(x + 1, y | (1 << x), max(xl, X1[x]), min(xr, X2[x]), max(yl, Y1[x]), min(yr, Y2[x]));
}

struct HyperKnight{
	LL countCells(int a, int b, int numRows, int numCols, int k){
		n = numRows, m = numCols;
		add(a + 1, n, b + 1, m);
		add(a + 1, n, 1, m - b);
		add(1, n - a, b + 1, m);
		add(1, n - a, 1, m - b);
		swap(a, b);
		add(a + 1, n, b + 1, m);
		add(a + 1, n, 1, m - b);
		add(1, n - a, b + 1, m);
		add(1, n - a, 1, m - b);
		swap(a, b);
		
		dfs(1, 0, 1, n, 1, m);
		PER(i, (1 << 9) - 1, 0){
			FOR(j, i + 1, 1 << 9) if((j & i) == i) F[i] -= F[j];
		}
		
		LL ans = 0;
		FOR(i, 0, 1 << 9){
			int one = 0;
			for(int j = 0; j < 9; j ++) if((i >> j) & 1) one ++;
			if(one == k) ans += F[i];
		}
		return ans;
	}
}stu;