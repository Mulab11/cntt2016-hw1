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

int use[65];
LL num[65];

struct BitwiseAnd{
	vector<LL> lexSmallest(vector<LL> S, int n){
		for(auto u : S)
		for(auto v : S){
			if(u == v) continue;
			if(!(u & v)) return vector<LL>();
			for(auto w : S){
				if(w == v || u == w) continue;
				if(u & v & w) return vector<LL>();
			}
		}
		for(auto u : S) for(auto v : S) if(u ^ v){
			LL k = u & v;
			FOR(b, 0, 60) if((k >> b) & 1) use[b] = 1; 
		}
		FOR(i, S.size(), n){
			for(auto u : S){
				int fd = 0;
				FOR(b, 0, 60) if(((u >> b) & 1) && !use[b]){
					fd = 1;
					use[b] = 1;
					num[i] |= 1LL << b;
					break;
				}
				if(!fd) return vector<LL>();
			}
		}
		for(auto u : S) FOR(b, 0, 60) if((u >> b) & 1) use[b] = 1;
		FOR(i, S.size(), n)
		FOR(j, i + 1, n){
			int fd = 0;
			FOR(b, 0, 60) if(!use[b]){
				use[b] = 1;
				num[i] |= 1LL << b;
				num[j] |= 1LL << b;
				fd = 1;
				break;
			}
			if(!fd) return vector<LL>();
		}
		vector<LL> ans;
		for(auto u : S) ans.pb(u);
		FOR(i, S.size(), n) ans.pb(num[i]);
		sort(ans.begin(), ans.end());
		return ans;
	}
}stu;