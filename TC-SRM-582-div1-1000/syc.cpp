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

int vis[N];
int mu[N], mu2[N], mu3[N];
int s3n, s4n;
LL ans = 0;
VI cnt[20005], fac[20005];
struct SemiPerfectPower{
	int Sqrt(LL x, int v){
		int L = 0, R = 0, aim = L;
		if(v == 2){
			R = 282842713;
		}else
		if(v == 3){
			R = 430887;
		}else{
			R = 16818;
		}
		while(L <= R){
			int md = (L + R) / 2;
			LL val = 1;
			REP(i, 1, v) val *= md;
			if(val <= x){
				aim = md;
				L = md + 1;
			}else{
				R = md - 1;
			}
		}
		return aim;
	}
	LL work(LL n){
		s3n = Sqrt(n, 3);
		s4n = Sqrt(n, 4);
		ans = 0;
		REP(i, 1, s3n)if(mu2[i]){
			int u = Sqrt(n / i, 2);
			if(u <= i) break;
			ans += u - i;
		}
		REP(a, 1, s4n)if(mu3[a]){
			for(int k = 1; 1LL * k * k * k <= a; k ++){
				int k2 = k * k, d = __gcd(k2, a);
				int w = a / d;
				if(!mu2[w]) continue;
				int t = k2 / d;
				int L = a / t;
				int R = Sqrt(n / (1LL * a * t * t * t), 3);
				if(L <= R){
					for(int c : fac[w]){
						ans += mu[c] * (cnt[c][R / c] - cnt[c][L / c]);
					}
				}
			}
		}
		return ans;
	}
	
	void pret(){
		int lim = 430900;
		REP(i, 1, lim) mu[i] = mu3[i] = 1;
		REP(i, 2, lim)if(!vis[i]){
			for(int j = i; j <= lim; j += i) mu[j] = -mu[j];
			for(int j = i + i; j <= lim; j += i) vis[j] = 1;
			int sqi = i * i;
			if(i <= 1000) for(int j = sqi; j <= lim; j += sqi) mu[j] = 0;
			sqi *= i;
			if(i <= 100) for(int j = sqi; j <= lim; j += sqi) mu3[j] = 0;
		}
		dprintf("%d\n", (int)clock());
		REP(i, 1, 16818) if(mu[i]) for(int j = i; j <= 16818; j += i) fac[j].pb(i);
		dprintf("%d\n", (int)clock());
		REP(i, 1, lim) if(mu[i]) mu2[i] = 1;
		REP(i, 1, 16818){
			cnt[i].pb(0);
			for(int j = i; j <= lim; j += i){
				int u = cnt[i].back() + mu2[j];
				cnt[i].pb(u);
			}
		}
		dprintf("%d\n", (int)clock());
	}
	
	LL count(LL L, LL R){
		pret();
		return work(R) - work(L - 1);
	}
}s;