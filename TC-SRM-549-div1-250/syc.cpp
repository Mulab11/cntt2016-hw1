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
VI e[N];
int lk[N], vis[N];

int find(int x){
	if(!x) return 1;
	for(auto v : e[x]){
		if(!vis[v]){
			vis[v] = 1;
			if(find(lk[v])){
				lk[v] = x;
				return 1;
			}
		}
	}
	return 0;
}

struct PointyWizardHats{
	int getNumHats(VI tH, VI tR, VI bH, VI bR){
		int res = 0;
		n = tH.size();
		m = bH.size();
		FOR(i, 0, tH.size())
		FOR(j, 0, bH.size()){
			if(bR[j] > tR[i]){
				db k1 = 1.0 * tR[i] / tH[i];
				db k2 = 1.0 * bR[j] / bH[j];
				if(k1 < k2){
					e[i + 1].pb(j + 1);
				}
			}
		}
		REP(i, 1, n){
			memset(vis, 0, sizeof vis);
			if(find(i)) res++;
		}
		return res;
	}
} stu;