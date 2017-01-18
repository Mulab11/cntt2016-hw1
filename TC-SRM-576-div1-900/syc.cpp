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
const	int P=1e9+9;
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
LL A[15][15];
char B[15][15];
set<LL> st[2];
set<LL> yue[2];
struct CharacterBoard{
	
	int calc(int l, int r, int w){
		if(l > r) return 0;
		return 1LL * (Pow(w, l, P) + P - Pow(w, r + 1, P)) * Pow(1 + P - w, P - 2, P) % P;
	}
	
	int countGenerators(vector<string> fragment, int w, int i0, int j0){
		n = fragment.size();
		m = fragment[0].size();
		REP(i, 1, n) REP(j, 1, m){
			B[i][j] = fragment[i - 1][j - 1];
			A[i][j] = 1LL * (i0 + i - 1) * w + (j0 + j - 1);
		}
		REP(i, 1, n) REP(j, 1, m)
		REP(ii, 1, n) REP(jj, 1, m){
			if(ii == i && jj == j) continue;
			LL c = abs(A[ii][jj] - A[i][j]);
			int bidx = B[i][j] != B[ii][jj];
			if(yue[bidx].count(c)) continue;
			yue[bidx].insert(c);
			for(LL x = 1; x * x <= c; x ++) if(c % x == 0){
				LL u = x, v = c / x;
				if(u <= w){
					st[bidx].insert(u);
				}
				if(v <= w){
					st[bidx].insert(v);
				}
			}
		}
		
		int ans = calc(0, w - n * m, 26);
		for(auto v : st[1])if(v >= n * m) ans = (ans + P - Pow(26, v - n * m, P)) % P;
		for(auto v : st[0]){
			if(st[1].count(v)) continue;
			if(v >= n * m) ans = (ans + P - Pow(26, v - n * m, P)) % P;
			set<LL> mps;
			mps.clear();
			REP(i, 1, n) REP(j, 1, m) mps.insert(A[i][j] % v);
			renew(ans, Pow(26, v - mps.size(), P));
		}
		
		return ans;
	}
};