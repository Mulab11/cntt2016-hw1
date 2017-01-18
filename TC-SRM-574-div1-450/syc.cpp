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
const	int N=25;

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

LL f[1 << 18][18];
int A[N][N];
struct PolygonTraversal{
	LL count(int n, VI points){
		int st = 0;
		for(auto v : points) st |= 1 << (v - 1);
		f[st][points.back() - 1] = 1;
		
		//预处理出i->j这条线会穿过哪些端点.
		REP(i, 1, n) REP(j, i + 1, n) REP(k, 1, n) if(k != i && k != j){
			if(i < k && k < j) A[i][j] |= 1 << (k - 1);
			else A[j][i] |= 1 << (k - 1);
		}
		
		//用f[s][i]表示已经确定的额点的集合是S,最后一个点是i的方案数
		//枚举一个不在s中的点k,如果线段ik将S分成两半,那么就合法,否则不合法.
		for(int i = st; i < (1 << n); i ++){
			for(int j = 0; j < n; j ++){
				LL val = f[i][j];
				if(!val) continue;
				//枚举k,检查其是否合法.
				for(int k = 0; k < n; k ++)if(!((i >> k) & 1) && (A[j + 1][k + 1] & i) && (A[k + 1][j + 1] & i)){
					f[i | (1 << k)][k] += val;
				}
			}
		}
		
		//计算答案.
		LL ans = 0;
		for(int i = 0; i < n; i ++) if(A[points[0]][i + 1] && A[i + 1][points[0]]) ans += f[(1 << n) - 1][i];
		return ans;
	}
}stu;