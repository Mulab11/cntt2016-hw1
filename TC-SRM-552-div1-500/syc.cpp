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

int n, m, D;
int S[55][55], G[55][55];
int S1[5555], S2[5555];

struct FoxAndFlowerShopDivOne{
	int get(int xl, int xr, int yl, int yr){
		xl--;
		yl--;
		return S[xr][yr] + S[xl][yl] - S[xr][yl] - S[xl][yr];
	}
	int Get(int xl, int xr, int yl, int yr){
		xl--;
		yl--;
		return G[xr][yr] + G[xl][yl] - G[xr][yl] - G[xl][yr];		
	}
	int calcx(){
		int res = -1;
		FOR(p, 1, n){
			memset(S1, -1, sizeof S1);
			memset(S2, -1, sizeof S2);
			REP(i, 1, p)
			REP(j, i, p)
			REP(k, 1, m)
			REP(l, k, m){
				chkmax(S1[get(i, j, k, l) + 2500], Get(i, j, k, l));
			}
			REP(i, p + 1, n)
			REP(j, i, n)
			REP(k, 1, m)
			REP(l, k, m){
				chkmax(S2[get(i, j, k, l) + 2500], Get(i, j, k, l));
			}
			
			REP(i, 0, 5000) if(S1[i] != -1)
			REP(j, 0, 5000) if(S2[j] != -1 && abs(i + j - 5000) <= D){
				chkmax(res, S1[i] + S2[j]);
			}
		}
		return res;
	}
	int calcy(){
		int res = -1;
		FOR(p, 1, m){
			memset(S1, -1, sizeof S1);
			memset(S2, -1, sizeof S2);
			REP(i, 1, n)
			REP(j, i, n)
			REP(k, 1, p)
			REP(l, k, p){
				chkmax(S1[get(i, j, k, l) + 2500], Get(i, j, k, l));
			}
			REP(i, 1, n)
			REP(j, i, n)
			REP(k, p + 1, m)
			REP(l, k, m){
				chkmax(S2[get(i, j, k, l) + 2500], Get(i, j, k, l));
			}
			
			REP(i, 0, 5000) if(S1[i] != -1)
			REP(j, 0, 5000) if(S2[j] != -1 && abs(i + j - 5000) <= D){
				chkmax(res, S1[i] + S2[j]);
			}
		}
		return res;
	}
	int theMaxFlowers(vector<string> flowers, int maxDiff){
		n = flowers.size();
		m = flowers[0].size();
		D = maxDiff;
		REP(i, 1, n) REP(j, 1, m){
			if(flowers[i - 1][j - 1] == 'L') S[i][j] = 1;
			else if(flowers[i - 1][j - 1] == 'P') S[i][j] = -1;
			else S[i][j] = 0;
			
			G[i][j] = flowers[i - 1][j - 1] == '.' ? 0 : 1;
		}
		REP(i, 1, n) REP(j, 1, m) S[i][j] += S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1];
		REP(i, 1, n) REP(j, 1, m) G[i][j] += G[i - 1][j] + G[i][j - 1] - G[i - 1][j - 1];
		return max(calcx(), calcy());
	}
} stu;