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
const	int N=355;

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

int n;
struct PenguinEmperor{
	int G[N][N], C[N];
	int tmp1[N], tmp2[N];
	int ans[N], rr[N];
	void mult(int *a, int *b){
		memset(C, 0, sizeof C);
		FOR(i, 0, n) FOR(j, 0, n){
			renew(C[(i + j) % n], 1LL * a[i] * b[j] % P);
		}
		FOR(i, 0, n) a[i] = C[i];
	}
	void mult(int *a, int c, int *to){
		FOR(i, 0, n) to[i] = 0;
		FOR(i, 0, n) to[(i + c) % n] = a[i];
	}
	int countJourneys(int nums, LL days){
		n = nums;
		LL rnds = days / nums;
		int rst = days % nums;
		G[0][0] = 1;
		REP(i, 1, n){
			mult(G[i - 1], i % n, tmp1);
			mult(G[i - 1], (n - i) % n, tmp2);
			if(i % n == (n - i) % n){
				memset(tmp2, 0, sizeof tmp2);
			}
			FOR(x, 0, n) G[i][x] = (tmp1[x] + tmp2[x]) % P;
		}
		FOR(x, 0, n) rr[x] = G[n][x];
		ans[0] = 1;
		for(; rnds; rnds >>= 1, mult(rr, rr)) if(rnds & 1) mult(ans, rr); 
		mult(ans, G[rst]);
		return ans[0];
	}
}stu;