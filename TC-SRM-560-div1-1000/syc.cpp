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

int ms, n;
db val[15], ans;
int e[15][15], stat[15];
VI low, up, c;

void dfs(int x, int sum){
	if(sum < 0) return;
	if(x == n){
		FOR(i, 0, n){
			if(!stat[i]) val[i] = low[i];
			if(stat[i] == 1) val[i] = up[i];
			if(stat[i] == 2) val[i] = 0;
		}
		if(c.size()){
			db gt = -sum;
			for(auto v : c){
				FOR(i, 0, n) if(e[v][i] && stat[i] != 2) val[v] += val[i];
				val[v] += sum * 0.5;
				gt += val[v];
			}
			gt /= c.size();
			for(auto v : c) val[v] -= gt;
			for(auto v : c){
				if(val[v] < low[v] || val[v] > up[v]) return;
			}
		}
		
		db res = 0;
		FOR(i, 0, n)
		FOR(j, i, n) if(e[i][j]) res += val[i] * val[j];
		chkmax(ans, res);
		return;
	}
	stat[x] = 0;
	dfs(x + 1, sum - low[x]);
	stat[x] = 1;
	dfs(x + 1, sum -  up[x]);
	int ok = 1;
	stat[x] = 2;
	for(auto v : c) if(!e[v][x]){
		ok = 0;
		break;
	} 
	if(ok){
		c.pb(x);
		dfs(x + 1, sum);
		c.pop_back();
	}
}

struct BoundedOptimization{
	db maxValue(vector<string> expr, VI lowerBound, VI upperBound, int maxSum){
		string Exp = "";
		for(auto v : expr) Exp += v;
		for(int i = 0; i < (int)Exp.length(); ){
			int u = Exp[i] - 'a'; i ++;
			int v = Exp[i] - 'a'; i ++;
			e[u][v] = e[v][u] = 1;
			i ++;
		}
		
		ms  = maxSum;
		low = lowerBound;
		up  = upperBound;
		n   = up.size();
		
		dfs(0, ms);
		return ans;
	}
}stu;