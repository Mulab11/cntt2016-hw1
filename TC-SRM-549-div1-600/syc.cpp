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

int m;
int hats, n;
char mps[15][15];
int X[15], Y[15], C, K, H;
int rx[15], ry[15];
int dp[1600005];
int cur[15];
int occ[15];

int get(int *a){
	int res = 0;
	PER(i, C - 1, 0) res = (res * 3 + a[i]);
	return res;
}

void dfs_valid(int x, int y){
	if(x > C){
		if(y != H) return;
		int ok = 1;
		REP(i, 1, n) rx[i] = 0;
		REP(i, 1, m) ry[i] = 0;
		REP(i, 1, C){
			rx[X[i]] ^= occ[i] ^ 1;
			ry[Y[i]] ^= occ[i] ^ 1;
		}
		REP(i, 1, n) if(rx[i]) ok = 0;
		REP(i, 1, m) if(ry[i]) ok = 0;
		if(ok){
			FOR(cov, 0, 1 << C){
				int cnt = 0;
				FOR(i, 0, C) cnt += !((cov >> i) & 1);
				if(cnt != K) continue;
				FOR(i, 0, C) cur[i] = ((cov >> i) & 1) ? 0 : (occ[i + 1] + 1);
				
				int tms = 0;
				FOR(i, 0, C) tms += cur[i] == 2;
				dp[get(cur)] = 0;
			}
		}
		return;
	}
	
	occ[x] = 0;
	dfs_valid(x + 1, y);
	
	occ[x] = 1;
	dfs_valid(x + 1, y + 1);
}

struct MagicalHats{
	int findMaximumReward(vector<string> board, VI coins, int numGuesses){
		n = board.size();
		m = board[0].size();
		REP(i, 1, n) REP(j, 1, m){
			mps[i][j] = board[i - 1][j - 1];
			if(mps[i][j] == 'H'){
				++ C;
				X[C] = i;
				Y[C] = j;
			}
		}
		K = numGuesses;
		H = coins.size();
		
		memset(dp, -1, sizeof dp);
		dfs_valid(1, 0);
		
		int U = 0;
		FOR(i, 0, C) U = U * 3 + 2;
		PER(st, U, 0){
			int now = st, tms = 0;
			FOR(i, 0, C){
				cur[i] = now % 3;
				tms += cur[i] != 0;
				now /= 3;
			}
			if(tms >= K) continue;
			int res = -1;
			FOR(i, 0, C)if(!cur[i]){
				cur[i] = 1;
				int w = inf, tmp;
				tmp = dp[get(cur)];
				if(tmp >= 0) w = min(w, tmp);
				cur[i] = 2;
				tmp = dp[get(cur)];
				if(tmp >= 0) w = min(w, tmp + 1);
				if(w == inf) w = -1;
				chkmax(res, w);
				cur[i] = 0;
			}
			dp[st] = res;
		}
		
		sort(coins.begin(), coins.end());
		
		if(dp[0] < 0) return -1;
				
		int ans = 0;
		FOR(i, 0, dp[0]) ans += coins[i];
		return ans;
	}
} stu;