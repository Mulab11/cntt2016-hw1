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
const	int N=15;

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
int val[N], dp[N];
int f1[1 << N], f2[1 << N], U, ans = 1 << 30;

#define Cnt(x) __builtin_popcount(x)

struct YetAnotherBoardGame{
	int minimumMoves(vector<string> board){
		n = board.size();
		m = board[0].size();
		U = (1 << m) - 1;
		FOR(i, 0, n) FOR(j, 0, m) if(board[i][j] == 'W') val[i] |= 1 << j;
		FOR(st, 0, 1 << m){
			f1[st] = ((st << 1) & U) ^ (st >> 1);
			f2[st] = f1[st] ^ st;
		}
		FOR(fx, 0, 1 << m){
			int fy = ((1 << m) - 1) ^ fx;
			for(int s = fx; ; s = (s - 1) & fx){
				int res = Cnt(s);
				REP(i, 0, n) dp[i] = val[i];
				dp[0] ^= f1[s];
				dp[1] ^= s;
				FOR(i, 1, n){
					if(dp[i - 1]){
						int s = dp[i - 1];
						int t1 = (fx & s) == s;
						int t2 = (fy & s) == s;
						res += Cnt(s);
						if(t1){
							dp[i] ^= f1[s];
							dp[i + 1] ^= s;
						}else
						if(t2){
							dp[i] ^= f2[s];
							dp[i + 1] ^= s;
						}else{
							res = 1 << 30;
							break;
						}
					}
				}
				if(dp[n - 1]) res = 1 << 30;
				chkmin(ans, res);
				if(!s) break;
			}
			for(int s = fy; ; s = (s - 1) & fy){
				int res = Cnt(s);
				REP(i, 0, n) dp[i] = val[i];
				dp[0] ^= f2[s];
				dp[1] ^= s;
				FOR(i, 1, n){
					if(dp[i - 1]){
						int s = dp[i - 1];
						int t1 = (fx & s) == s;
						int t2 = (fy & s) == s;
						res += Cnt(s);
						if(t1){
							dp[i] ^= f1[s];
							dp[i + 1] ^= s;
						}else
						if(t2){
							dp[i] ^= f2[s];
							dp[i + 1] ^= s;
						}else{
							res = 1 << 30;
							break;
						}
					}
				}
				if(dp[n - 1]) res = 1 << 30;
				chkmin(ans, res);
				if(!s) break;
			}
		}
		if(ans > 1e9) ans = -1;
		return ans;
	}
}stu;