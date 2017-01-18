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

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};
int use[155][155];
int minx, maxx, miny, maxy;

struct RotatingBot{
	int minArea(VI A){
		int x = 100, y = 100, d = 0;
		int stp = 0;
		use[x][y] = 1;
		miny = minx = maxx = maxy = 100;
		for(auto v : A){
			REP(i, 1, v){
				++stp;
				x = x + dx[d];
				y = y + dy[d];
				chkmax(maxx, x);
				chkmin(minx, x);
				chkmax(maxy, y);
				chkmin(miny, y);
				if(use[x][y]) return -1;
				use[x][y] = 1;
			}
			d = (d + 1) & 3;
		}
		
		memset(use, 0, sizeof use);
		x = 100, y = 100, d = 0;
		use[x][y] = 1;
		int now = 0;
		VI B = {};
		REP(a, 1, stp){
			int nx = x + dx[d];
			int ny = y + dy[d];
			if(nx < minx || nx > maxx || ny < miny || ny > maxy || use[nx][ny]){
				B.pb(now);
				now = 0;
				d = (d + 1) & 3;
				nx = x + dx[d];
				ny = y + dy[d];
				if(nx < minx || nx > maxx || ny < miny || ny > maxy || use[nx][ny]){
					break;
				}
				--a;
			}else{
				x = nx;
				y = ny;
				use[x][y] = 1;
				++now;
			}
		}
//		for(auto v : B) printf("%d ", v); puts("");
		if(now) B.pb(now);
		if(B == A){
			return (maxx - minx + 1) * (maxy - miny + 1);
		}else return -1;
	}
} stu;