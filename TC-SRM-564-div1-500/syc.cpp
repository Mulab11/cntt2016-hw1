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

int n, k;
LL ans = 0;
void check1(int x){
	//x + n - r = k - 1
	int r = x + n - k + 1;
	if(r <= x) return;
	//g + b = n - r
	//g <= x
	//n - r - g <= x
	//n - r - x <= g
	ans += max(0, min(x, n - r) - max(0, (n - r - x)) + 1);
}

void check2(int x){
	//g > l, b <= l
	//l + l + b = k - 1
	int b = k - 1 - x - x;
	if(b < 0 || b > x) return;
	//r + g = n - b
	//g > l
	//n - b - g > l
	//l < g < n - b - l
	ans += max(0, max(0, n - b - x - x - 1));
}

void check3(int x){
	//g <= l, b > l
	//l + l + g = k - 1
	int g = k - 1 - x - x;
	if(g < 0 || g > x) return;
	ans += max(0, max(0, n - g - x - x - 1));
}

void check4(int x){
	if(3 * x != k - 1) return;
	//r > x, g > x, b > x, r + g + b = n
	int tn = n - 3 * x;
	if(tn <= 1) return;
	ans += 1LL * (tn - 1) * (tn - 2) / 2;
}

struct AlternateColors2{
	LL countWays(int n, int k){
		:: n = n;
		:: k = k;
		if(k == 1){
			return 1LL * n * (n + 1) / 2;
		}
		FOR(l, 1, k){
			check1(l);
			check2(l);
			check3(l);
			check4(l);
		}
		return ans;
	}
}a;