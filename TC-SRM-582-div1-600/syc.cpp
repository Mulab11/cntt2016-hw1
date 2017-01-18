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
const	int P=1e9+9;
const	int N=1305;

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

int n, cnt;
string w1, w2;
int WK[N][N];
int DP[N][N], fac[N], inv[N];
int sum1[N], sum2[N], col[N];
map<pair<char, char>, int> mps;
struct ColorfulBuilding{
	int count(vector<string> color1, vector<string> color2, int L){
		for(auto w : color1) w1 += w;
		for(auto w : color2) w2 += w;
		n = w1.length();
		REP(i, 1, n){
			int &v = mps[mk(w1[i - 1], w2[i - 1])];
			if(!v) v = ++cnt;
			col[i] = v;
		}
		
		fac[0] = inv[0] = 1;
		REP(i, 1, n) fac[i] = 1LL * fac[i - 1] * i % P;
		REP(i, 1, n) inv[i] = Pow(fac[i], P - 2, P) % P;
		
		WK[n][1] = 1;
		DP[n][1] = 1;
		REP(c, 1, L){
			memset(sum1, 0, sizeof sum1);
			memset(sum2, 0, sizeof sum2);
			int usum = 0;
			PER(i, n, 1){
				renew(DP[i][c], 1LL * usum         * fac[n - i - 1] % P);
				renew(DP[i][c], 1LL * sum1[col[i]] * fac[n - i - 1] % P);
				renew(DP[i][c], 1LL * sum2[col[i]] * fac[n - i - 1] % P);
				renew(sum1[col[i]],  1LL * DP[i][c]     * inv[n - i] % P);
				renew(sum2[col[i]], -1LL * DP[i][c - 1] * inv[n - i] % P);
				renew(usum,          1LL * DP[i][c - 1] * inv[n - i] % P);
				
			}
		}
		
		int ans = 0;
		REP(i, 1, n) renew(ans, 1LL * DP[i][L] * fac[n - 1] % P * inv[n - i] % P);
		return ans;
	}
}stu;