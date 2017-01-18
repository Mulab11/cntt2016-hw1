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
const	int N=500005;

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

int X[N], Y[N], n, m;
int fac[N], inv[N];
struct WolfPack{
	int C(int x, int y){
		if(x < y || y < 0) return 0;
		return 1LL * fac[x] * inv[y] % P * inv[x - y] % P;
	}
	int work(int *a){
		int ans = 0;
		REP(re, -300000, 300000){
			int res = 1;
			REP(i, 1, n){
				if(((a[i] - re) & 1) != (m & 1)){
					res = 0;
					break;
				}
				int up = (m + a[i] - re) / 2;
				res = 1LL * res * C(m, up) % P;
			}
			renew(ans, res);
		}
		return ans;
	}
	int calc(VI x, VI y, int m){
		n = x.size();
		::m = m;
		fac[0] = inv[0] = 1;
		REP(i, 1, 500000) fac[i] = 1LL * fac[i - 1] * i % P;
		REP(i, 1, 500000) inv[i] = Pow(fac[i], P - 2, P);
		REP(i, 1, n){
			X[i] = x[i - 1] + y[i - 1];
			Y[i] = x[i - 1] - y[i - 1];
		}
		return 1LL * work(X) * work(Y) % P;
	}
}stu;