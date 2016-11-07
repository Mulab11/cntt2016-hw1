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
const	int N=105;

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

PII V[N];
LL dp[N], to[N], ddd[N];
LL cb[N << 1][N << 1];
int n, K, dif, tot;
int has[N], dep[N], now[N], sz[N], cnt, a[N], no;

LL res = 0;
int cancho = 0;
struct Excavations{
	
	void count(int u){
		//如果一种建筑now[i]==sz[i],说明这种建筑还没出现过,这种情况不合法.
		REP(i, 1, cnt) if(now[i] == sz[i]) return;
		//将生成函数的分子加到记录分子和的数组中去.
		REP(i, 0, n - u) ddd[i + u] += dp[i];
	}
	
	void Div(int l, int r){
		//将分子除掉(x^l-x^r)
		memset(to, 0, sizeof to);
		REP(i, 0, n) to[i] = dp[i + l];
		REP(i, 0, n) if(i >= r - l) to[i] += to[i - (r - l)];
		REP(i, 0, n) dp[i] = to[i];
	}
	
	void Mul(int l, int r){
		//将分子乘上(x^l-x^r)
		memset(to, 0, sizeof to);
		REP(i, 0, n){
			if(i >= l) to[i] += dp[i - l];
			if(i >= r) to[i] -= dp[i - r];
		}
		REP(i, 0, n) dp[i] = to[i];
	}
	
	LL Main(){
		//把所有的建出拎出来,按照深度排序.
		//注意没有出现在found中的建筑要排在同深度建筑的最前面.
		REP(i, 1, n){
			if(has[a[i]]){
				V[++tot] = mk(dep[i], has[a[i]]);
			}else{
				V[++tot] = mk(dep[i], -1);
				no ++;
				//cancho用来维护不在found中的建筑对分子的贡献.
				cancho ++;
			}
		}
		
		sort(V + 1, V + tot + 1);
		
		dp[0] = 1;
		dif = K - cnt - (no > 0);
		//因为分母不变,用ddd[i]表示生成函数的分子和.
		memset(ddd, 0, sizeof ddd);
		//因为每次转移的右端点不变,用now[i]表示当前的左端点.
		//F(x) = x^cancho*\prod{i=1}^{cnt}{(x^now[i]-x^sz[i])/(1-x)}
		memset(now, -1, sizeof now);
		REP(u, 1, cnt) now[u] = sz[u];
		REP(i, 1, tot){
			if(V[i].se == -1){
				//计算答案.
				-- cancho;
				count(cancho);
			}else{
				//维护分子
				int u = V[i].se;
				if(now[u] != sz[u]) Div(now[u], sz[u]);
				--now[u];
				Mul(now[u], sz[u]);
			}
		}
		REP(i, 0, n) REP(j, i, n) res += ddd[i] * cb[j - i + cnt - 1][cnt - 1] * cb[j][dif];

		dif = K - cnt;
		memset(ddd, 0, sizeof ddd);
		count(0);
		REP(i, 0, n) REP(j, i, n) res += ddd[i] * cb[j - i + cnt - 1][cnt - 1] * cb[j][dif];
		return res;
	}
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
		for(auto v : knd) if(has[v]) sz[has[v]]++;
		return Main();
	}
} stu;

int main(){
	cout << stu.count({1, 1, 2, 2}, {10, 15, 10, 20}, {1}, 2) << endl;
	return 0;
}






