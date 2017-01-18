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

int n, m;
char mps[N][N];

struct TwoConvexShapes{
	int Up[N][N], Dn[N][N], res;
	
	void work(){
		memset(Up, 0, sizeof Up);
		memset(Dn, 0, sizeof Dn);
		
		Up[0][1] = 1;
		Dn[0][m + 1] = 1;
		REP(i, 1, n){
			REP(k, 1, m + 1){
				REP(j, k, m + 1){
					int ok = 1;
					REP(x, 1, j - 1) if(mps[i][x] == 'W') ok = 0;
					REP(x, j, m) if(mps[i][x] == 'B') ok = 0;
					if(ok) renew(Up[i][j], Up[i - 1][k]);
				}
			}
			
			REP(k, 1, m + 1){
				REP(j, 1, k){
					int ok = 1;
					REP(x, 1, j - 1) if(mps[i][x] == 'W') ok = 0;
					REP(x, j, m) if(mps[i][x] == 'B') ok = 0;
					if(ok) renew(Dn[i][j], Dn[i - 1][k]);
				}
			}
		}
		
		int ans = 0;
		REP(i, 1, m + 1){
			renew(ans, Up[n][i]);
			renew(ans, Dn[n][i]);
		}
		
		
		REP(j, 1, m + 1){
			int ok = 1;
			REP(i, 1, n){
				REP(x, 1, j - 1) if(mps[i][x] == 'W') ok = 0;
				REP(x, j, m) if(mps[i][x] == 'B') ok = 0;
			}
			renew(ans, -ok);
		}
		
		
		renew(res, ans);
		
		int pp = (P + 1) / 2;
		REP(i, 1, n){
			int ok1 = -pp;
			int ok2 = -pp;
			REP(j, 1, i){
				REP(k, 1, m){
					if(mps[j][k] == 'W') ok2 = 0;
					if(mps[j][k] == 'B') ok1 = 0;
				}
			}
			REP(j, i + 1, n){
				REP(k, 1, m){
					if(mps[j][k] == 'W') ok1 = 0;
					if(mps[j][k] == 'B') ok2 = 0;
				}
			}
			
			renew(res, ok1);
			renew(res, ok2);
		}
	}
	
	int countWays(vector<string> maps){
		n = maps.size();
		m = maps[0].size();
		REP(i, 1, n)
		REP(j, 1, m) mps[i][j] = maps[i - 1][j - 1];
		
		work();
		REP(i, 1, n) REP(j, 1, m){
			if(mps[i][j] == 'W') mps[i][j] = 'B';
			else if(mps[i][j] == 'B') mps[i][j] = 'W';
		}
		work();
		
		return res;
	}
} stu;