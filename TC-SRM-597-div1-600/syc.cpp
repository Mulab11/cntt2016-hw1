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

int n, m;
struct po{
	int x, y;
}A[300005];

map<PII, int> mps;

struct ConvexPolygonGame{

	int Push(int x, int y){
		if(mps.count(mk(x, y))) return 1;
		if(m == 300000) return 0;
		A[++m] = (po){x, y};
		return 1;
	}

	double Yat(int x, int x1, int x2, int y1, int y2){
		double k = 1.0 * (y2 - y1) / (x2 - x1);
		return y1 + k * (x - x1);
	}

	string winner(VI X, VI Y){
		n = X.size();
		FOR(i, 0, n) mps[mk(X[i], Y[i])] = 1;
		X.pb(X[0]);
		Y.pb(Y[0]);
		REP(x, -100000, 100000){
			int ymin =  1 << 30;
			int ymax = -1 << 30;
			FOR(i, 0, n){
				int x1 = X[i], x2 = X[i + 1];
				int y1 = Y[i], y2 = Y[i + 1];
				int Dn = (x1 <= x2);
				if(!Dn){
					swap(x1, x2);
					swap(y1, y2);
				}
				if(x1 <= x && x <= x2){
					if(x1 == x2){
						continue;
					}else{
						double val = Yat(x, x1, x2, y1, y2);
						if(val < min(y1, y2) || val > max(y1, y2)) continue;
						if(Dn){
							ymin = ceil(val);
						}else{
							ymax = floor(val);
						}
					}
				}
			}
			if(ymin == (1 << 30) || ymax == (-1 << 30)) continue;
			REP(i, ymin, ymax) if(!Push(x, i))
				return "Masha";
		}
		REP(i, 2, m) A[i].x -= A[1].x, A[i].y -= A[1].y;
		REP(i, 2, m) if(1LL * A[i].y * A[2].x != 1LL * A[i].x * A[2].y) return "Masha";
		return "Petya";
	}
}s;