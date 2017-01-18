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

int cnt, DP[25][25][25][25];
int n = 8, m = 8, X[155], Y[155];
struct EllysChessboard{
	int minCost(vector<string> board){
		REP(i, 0, 7)
		REP(j, 0, 7){
			if(board[i][j] == '#'){
				++cnt;
				X[cnt] = i + j;
				Y[cnt] = i - j + 7;
			}
		}
		
		if(!cnt) return 0;
		
		memset(DP, 0x3f, sizeof DP);
		REP(i, 1, cnt) DP[X[i]][X[i]][Y[i]][Y[i]] = 0;
		//0 <= X <= 14
		//0 <= Y <= 14
		REP(dx, 0, 14) REP(dy, 0, 14)
		REP(x, 0, 14 - dx) REP(y, 0, 14 - dy){
			int xl = x, xr = x + dx;
			int yl = y, yr = y + dy;
			int ter = 1;
			REP(i, 1, cnt){
				if(xl <= X[i] && X[i] <= xr && yl <= Y[i] && Y[i] <= yr) continue;
				ter = 0;
				int pxl = min(xl, X[i]);
				int pxr = max(xr, X[i]);
				int pyl = min(yl, Y[i]);
				int pyr = max(yr, Y[i]);
				int cost = 0;
				REP(j, 1, cnt){
				if(xl <= X[j] && X[j] <= xr && yl <= Y[j] && Y[j] <= yr) continue;
					if(pxl <= X[j] && X[j] <= pxr && pyl <= Y[j] && Y[j] <= pyr){
						int dist = max(X[j] - pxl, pxr - X[j]);
						dist = max(dist, max(Y[j] - pyl, pyr - Y[j]));
						cost += dist;
					}
				}
				chkmin(DP[pxl][pxr][pyl][pyr], DP[xl][xr][yl][yr] + cost);
			}
			if(ter) return DP[xl][xr][yl][yr];
		}
		return -1;
	}
}ss;