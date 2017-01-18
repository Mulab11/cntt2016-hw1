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

int dp[155];
struct Stamp{
	int getMinimumCost(string desiredColor, int StampCost, int pushCost){
		int res = 1 << 30;
		int n = desiredColor.size();
		REP(len, 1, n){
			int tmp = len * StampCost;
			memset(dp, 0x3f, sizeof dp);
			dp[0] = 0;
			REP(i, 0, n){
				REP(j, i + 1, n){
					int R = 0, G = 0, B = 0;
					REP(x, i + 1, j) if(desiredColor[x - 1] == 'R') R = 1;
					REP(x, i + 1, j) if(desiredColor[x - 1] == 'G') G = 1;
					REP(x, i + 1, j) if(desiredColor[x - 1] == 'B') B = 1;
					if(R + G + B > 1) continue;
					if(j - i < len) continue;
					dp[j] = min(dp[j], dp[i] + pushCost * ((j - i + len - 1) / len));
				}
			}
			
			chkmin(res, dp[n] + tmp);
		}
		return res;
	}
};