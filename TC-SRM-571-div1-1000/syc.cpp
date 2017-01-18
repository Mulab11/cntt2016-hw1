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
typedef long double	db;
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

int n;
int x[N], y[N], r[N];
db vl[N], vr[N];
map<PII, int> mps;
int vis[N], que[N * N * N];
struct CandyOnDisk{
	LL dis(int x1, int y1, int x2, int y2){
		return 1LL * (x1 - x2) * (x1 - x2) + 1LL * (y1 - y2) * (y1 - y2);
	}
	db Sqrt(db u){
		db l = 0, r = 2 * sqrt(u);
		REP(i, 1, 60){
			db md = (l + r) * .5;
			if(md * md <= u) l = md; else r = md;
		}
		return l;
	}
	string Main(int sx, int sy, int tx, int ty){
		int tail = 0;
		REP(i, 1, n){
			LL D = dis(sx, sy, x[i], y[i]);
			if(D <= 1LL * r[i] * r[i]){
				vl[i] = vr[i] = Sqrt(D);
				vis[que[++tail] = i] = 1;
			}else{
				vl[i] = 1e9;
				vr[i] = -vl[i];
			}
		}
		
		db zero = 0;
		db one = 1;
		
		REP(l, 1, tail){
			int u = que[l];
			vis[u] = 0;
			REP(to, 1, n)if(to != u){
				LL D = dis(x[to], y[to], x[u], y[u]);
				if(D > 1LL * (r[u] + r[to]) * (r[u] + r[to])) continue;
				db dis = Sqrt(D);
				db fl = max(zero, dis - r[to]), fr = min(one * r[u], dis + r[to]);
				if(fr < vl[u] || vr[u] < fl) continue;
				fl = max(zero, dis - r[u]), fr = min(one * r[to], dis + r[u]);
				if(fl < vl[to] || vr[to] < fr){
					chkmin(vl[to], fl);
					chkmax(vr[to], fr);
					if(!vis[to]) vis[que[++tail] = to] = 1;
				}
			}
		}
		
		REP(i, 1, n){
			db d = Sqrt(dis(tx, ty, x[i], y[i]));
			if(vl[i] <= d && d <= vr[i]) return "YES";
		}
		
		return "NO";
	}
	string ableToAchieve(VI x, VI y, VI r, int sx, int sy, int tx, int ty){
		if(sx == tx && sy == ty) return "YES";
		n = x.size();
		FOR(i, 0, n){
			int &val = mps[mk(x[i], y[i])];
			if(r[i] > val) val = r[i];
		}
		n = 0;
		for(auto v : mps){
			++n;
			::x[n] = v.fi.fi;
			::y[n] = v.fi.se;
			::r[n] = v.se;
		}
		return Main(sx, sy, tx, ty);
	}
}stu;