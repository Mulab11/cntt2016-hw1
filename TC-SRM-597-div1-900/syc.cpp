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

int fac[3000005], inv[3000005];
int f[3000005];
int x, y, z, tmp;
struct LittleElephantAndBoard{


	int C(int x, int y){
		if(x < 0 || y < 0 || x < y) return 0;
		return 1LL * fac[x] * inv[y] % P * inv[x - y] % P;
	}

	int work(int M, int R, int G, int B){
		if(R == 0 || G == 0) return 0;
		if((R + G + B) & 1) return 0;
		int ans = 0;
		x = ((R + G + B) >> 1) - B; 
		y = ((R + G + B) >> 1) - R; 
		z = ((R + G + B) >> 1) - G;
		tmp = 200;
		if(x < 0 || y < 0 || z < 0) return 0;
		if(y < z) swap(y, z);
		memset(f, 0, sizeof f);
		REP(i, 1, y){
			int v = C(y - 1, i - 1);
			if(i < x) renew(f[x - i - 1 + y - i], 1LL * v * C(x - 1, i) % P);
			if(i <= x) renew(f[x - i + y - i], 1LL * v * C(x - 1, i - 1) % P);
		}
		REP(i, 0, x + y - 2) renew(ans, 1LL * f[i] * C(x + y - i, z - i) % P);
		return ans;
	}

	int getNumber(int M, int R, int G, int B){
		fac[0] = inv[0] = 1;
		fac[1] = inv[1] = 1;
		int n = 2000000;
		REP(i, 2, n) fac[i] = 1LL * fac[i - 1] * i % P;
		REP(i, 2, n) inv[i] = 1LL * inv[P % i] * (P - P / i) % P;
		REP(i, 2, n) inv[i] = 1LL * inv[i - 1] * inv[i] % P;
		int ans = 0;
		renew(ans, work(M, R, G, B));
		renew(ans, work(M, R, B, G));
		renew(ans, work(M, G, R, B));
		renew(ans, work(M, G, B, R));
		renew(ans, work(M, B, R, G));
		renew(ans, work(M, B, G, R));
		return ans;
	}
}s;