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

int X[N], Y[N], Z[N], tot;

struct FindPolygons{
	double minimumPolygon(int L){
		if(L & 1) return -1;
		if(L == 2) return -1;
		REP(z, 1, L >> 1)
		REP(x, 0, z){
			int y = int(sqrt(z * z - x * x) + 0.5);
			if(x * x + y * y == z * z){
				++tot;
				X[tot] = x;
				Y[tot] = y;
				Z[tot] = z;
			}
		}
		int fd = 0;
		int ans = 1 << 30;
		REP(i, 1, tot) REP(j, i + 1, tot){
			int A = Z[i], B = Z[j];
			int dx = X[i] - X[j], dy = Y[i] - Y[j];
			int C = int(sqrt(dx * dx + dy * dy) + 0.5);
			int mx = max(max(A, B), C);
			int mn = min(min(A, B), C);
			if(C * C == dx * dx + dy * dy && A + B + C == L && L > 2 * mx){
				chkmin(ans, mx - mn);
				fd = 1;
			}
		}
		if(fd) return ans;
		return (L >> 1) & 1;
	}
}stu;