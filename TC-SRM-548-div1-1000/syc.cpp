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

int dp[N][N], P2[N * N], C[N];
int comb[N * N][N * N];

struct KingdomAndCities{
	int howMany(int n, int m, int K){
		P2[0] = 1;
		REP(i, 1, n * n) P2[i] = (P2[i - 1] << 1) % P;
		REP(i, 1, n) C[i] = (1LL * i * (i - 1) / 2) % P;
		REP(i, 0, n * n){
			comb[i][0] = 1;
			REP(j, 1, i) comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % P;
		}
		dp[0][0] = 1;
		REP(i, 1, n)
		REP(j, 0, K){
			dp[i][j] = comb[C[i]][j];
			FOR(k, 1, i)
			REP(l, 0, j){
				dp[i][j] = (dp[i][j] + P - 1LL * comb[i - 1][k - 1] * dp[k][l] % P * comb[C[i - k]][j - l] % P) % P;
			}
		}
		if(!m) return dp[n][K];
		if(m == 1){
			if(n == 1) return 0;
			int ans = 0;
			if(K >= 2){
				ans = (ans + 1LL * C[n - 1] * dp[n - 1][K - 2]) % P;
				REP(x, 1, n - 1)
				REP(c, 0, K - 2){
					int y = n - 1 - x;
					if(y < 1) continue;
					int d = K - 2 - c;
					ans = (ans + 1LL * x * y % P * dp[x][c] % P * dp[y][d] % P * comb[n - 2][x - 1]) % P;
				}
			}
			return ans;
		}
		if(m == 2){
			if(n == 2) return 0;
			int ans = 0;
			
			static int sq[555];
			REP(i, 1, n) sq[i] = 1LL * i * i % P;
			
			{
				int rst = n - 2;
				if(K >= 4){
					ans = (ans + 1LL * dp[rst][K - 4] * C[rst] % P * C[rst]) % P;
				}
				if(K >= 3){
					ans = (ans + 1LL * dp[rst][K - 3] * rst % P * rst) % P;
				}
			}
			
			{
				int rst = n - 2;
				REP(x, 1, rst){
					int y = rst - x;
					if(y < 1) continue;
					int res = 0;
					REP(c, 0, K - 4){
						int d = K - 4 - c;
						res = (res + 1LL * dp[x][c] * dp[y][d]) % P;
					}
					ans = (ans + 1LL * comb[rst - 1][x - 1] * res % P * sq[x] % P * sq[y]) % P;
					ans = (ans + 2LL * comb[rst][x] * res % P * C[x] % P * y % P * x) % P;
					
					res = 0;
					REP(c, 0, K - 3){
						int d = K - 3 - c;
						res = (res + 1LL * dp[x][c] * dp[y][d]) % P;
					}
					ans = (ans + 1LL * comb[rst][x] * res % P * x % P * y) % P;
				}
			}
			
			{
				int rst = n - 2;
				REP(x, 1, rst)
				REP(y, 1, rst){
					int z = rst - x - y;
					if(z < 1) break;
					REP(c, 0, K - 4)
					REP(d, 0, K - 4){
						int e = K - 4 - c - d;
						if(e < 0) break;
						ans = (ans + 1LL * comb[rst][x] * comb[rst - x][y] % P * dp[x][c] % P * dp[y][d] % P * dp[z][e] % P * x % P * sq[y] % P * z) % P;
					}
				}
			}
			
			return ans;
		}
		return -1;
	}
}stu;