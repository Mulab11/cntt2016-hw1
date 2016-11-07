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
#define ALL(x) (x).begin(), (x).end()
#define REP(i, x, y)   for(int i = (int)(x); i <= (int)(y); i++)
#define FOR(i, x, y)   for(int i = (int)(x); i <  (int)(y); i++)
#define PER(i ,x, y)  for(int i = (int)(x); i >= (int)(y); i--)
#define CH	         ch = getchar()
#define Exit(...)    printf(__VA_ARGS__), exit(0)
#define dln()        fprintf(stderr,"\n")
#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef double	  db;
typedef unsigned long long LL;
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

LL dp[N][N];
int n, K, dif;
LL cb[N << 1][N << 1];
int has[N], dep[N], a[N], cnt;
int duo[N], sz[N];
VI can[N], no;
LL ddd[N];

LL work(int x, int y){
	memset(dp, 0, sizeof dp);
	dp[0][y] = 1;
	REP(i, 1, cnt){
		duo[i] = 0;
		for(auto v : can[i]) if(v >= x) duo[i] ++;
	}
	REP(i, 1, cnt)
	REP(j, 0, n){
		LL val = dp[i - 1][j];
		if(!val) continue;
		//每次转移相当于乘多项式 x ^ duo[i] - x ^ sz[i]
		if(j + duo[i] <= n) dp[i][j + duo[i]] += val;
		if(j + sz[i] <= n) dp[i][j + sz[i]] -= val;
	}
	
	LL ans = 0;
	REP(i, 0, n) if(dp[cnt][i]) ddd[i] += dp[cnt][i];
		
	return ans;
}

struct Excavations{
	LL count(VI knd, VI depth, VI found, int K){
		
		REP(i, 0, 100){
			cb[i][0] = 1;
			REP(j, 1, i) cb[i][j] = (cb[i - 1][j - 1] + cb[i - 1][j]);
		}
		
		//初始化信息并将颜色分类.
		::K = K;
		n = depth.size();
		REP(i, 1, n) a[i] = knd[i - 1];
		REP(i, 1, n) dep[i] = depth[i - 1];
		for(auto v : found) has[v] = ++cnt;
		REP(i, 1, n){
			if(has[a[i]]){
				can[has[a[i]]].pb(dep[i]);
			}else{
				no.pb(dep[i]);
			}
		}
		REP(i, 1, cnt){
			sort(ALL(can[i]));
			reverse(ALL(can[i]));
			sz[i] = can[i].size();
		}
		sort(ALL(no));
		reverse(ALL(no));
		
		
		
		
		LL res = 0;		
		dif = cnt + (no.size() > 0);
		dif = K - dif;
		//因为分母是不变的,用ddd[i]表示所有情况下生成函数的分子和.
		memset(ddd, 0, sizeof ddd);
		for(int i = 0; i < (int)no.size(); i ++) res += work(no[i], i);
		//会发现生成函数的分母是 (1-x)^cnt, 展开后是 sum{j>=0}{C(j+cnt-1,cnt-1)x^j}
		REP(i, 0, n) REP(j, i, n) res += ddd[i] * cb[j - i + cnt - 1][cnt - 1] * cb[j][dif];

		//计算一下K元组的所有建筑都在found中的情况.
		dif = K - cnt;
		memset(ddd, 0, sizeof ddd);
		res += work(inf, 0);
		REP(i, 0, n) REP(j, i, n) res += ddd[i] * cb[j - i + cnt - 1][cnt - 1] * cb[j][dif];
		return res;
	}
} stu;

int main(){
	cout << stu.count({50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50}, {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3}, {50}, 18) << endl;
	return 0;
}






