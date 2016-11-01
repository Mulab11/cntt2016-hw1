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

LL comb[55][55];
int cnt[N], has[N];
int dif, K, n;
VI no;
VI can[55];
LL dp[55][55], ans;

struct Excavations{
	void work(int x, int rst){
		memset(dp, 0, sizeof dp);
		dp[0][rst] = 1;
		REP(i, 1, 50){
			if(!can[i].size()){
				//这种建筑没有出现在fnd里面,直接略过.
				REP(j, 0, 50) dp[i][j] = dp[i - 1][j];
				continue;
			}
			REP(j, 0, 50){
				if(!dp[i - 1][j]) continue;
				//枚举这一种的最小深度,更新无影响的建筑个数.
				FOR(k, 0, can[i].size()){
					if(can[i][k] >= x) break;
					dp[i][j + can[i].size() - k - 1] += dp[i - 1][j];
				}
			}
		}
		//用组合数计算答案.
		REP(i, 0, 50) ans += dp[50][i] * comb[i][K - dif];
	}
	LL count(VI knd, VI depth, VI fnd, int K){
		n = depth.size();
		:: K = K;
		//预处理组合数.
		REP(i, 0, n){
			comb[i][0] = 1;
			REP(j, 1, i) comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
		}
		for(auto v : fnd) has[v] = 1;
		
		//dif表示的是不同种类的建筑个数.
		//在fnd里面的kind(i)被认为两两不同,不在fnd里面的kind(i)被认为是同一种.
		FOR(i, 0, n) if(!has[knd[i]]){
			dif = 1;
			break;
		}
		dif += fnd.size();
		FOR(i, 0, n){
			if(has[knd[i]]){
				can[knd[i]].pb(depth[i]);
			}else{
				no.pb(depth[i]);
			}
		}
		
		//把没有出现在fnd里面的按照深度排序.
		//把出现在fnd里面的按kind分类后按深度排序.
		REP(i, 1, 50) sort(can[i].begin(), can[i].end());
		sort(no.begin(), no.end());
		//枚举没有出现在fnd里面的最小深度,此时无影响的建筑个数为no.size() - x - 1.
		FOR(x, 0, no.size()) work(no[x], no.size() - x - 1);
		//上述计算没有考虑到不探测属于no的建筑的情况.
		if(no.size()) dif--;
		work(inf, 0);
		return ans;
	}
} stu;

int main(){
	return 0;
}






