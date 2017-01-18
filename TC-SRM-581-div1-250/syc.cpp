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

int n, m, ww[N], cnt[N], res[N];
struct SurveillanceSystem{
	string getContainerInfo(string containers, VI reports, int L){
		n = containers.size();
		m = reports.size();
		REP(i, 0, n - L){
			FOR(j, 0, L) ww[i] += containers[i + j] == 'X';
		}
		FOR(i, 0, m) res[reports[i]]++;
		string res;
		FOR(x, 0, n){
			memset(cnt, 0, sizeof cnt);
			REP(y, 0, n - L) if(y + L <= x || y > x){
				cnt[ww[y]]++;
			}
			int flag = 1;
			REP(i, 0, n) if(cnt[i] < ::res[i]) flag = 0;
			if(!flag){
				res.pb('+');
			}else{
				int qu = 0;
				REP(j, 0, n - L){
					if(j <= x && j + L > x){
						if(::res[ww[j]]) qu = 1;
					}
				}
				res.pb(qu? '?' : '-');
			}
		}
		return res;
	}
}s1;