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

int mps[155];
PII A[155];
int tot, ans = 2e9, pc, nc;

void work(){
	FOR(i, 1, tot) if(A[i].se > A[i + 1].se) return;
	REP(s, -1, 2){
		int res = 0;
		REP(i, 1, tot) A[i].se += s * 26;
		REP(i, 1, tot){
			int j = i;
			int l = A[i].fi;
			int r = A[i].fi;
			while(A[j].se == A[i].se && j <= tot){
				l = min(l, A[j].fi);
				r = max(r, A[j].fi);
				++j;
			}
			if(A[i].se >= l) res += (A[i].se - l) * nc;
			if(r >= A[i].se) res += (r - A[i].se) * pc;
			i = j - 1;
		}
		chkmin(ans, res);
		REP(i, 1, tot) A[i].se -= s * 26;
	}
}

struct NextAndPrev{
	int getMinimum(int nextCost, int prevCost, string start, string goal){
		if(start == goal) return 0;
		memset(mps, -1, sizeof mps);
		pc = prevCost;
		nc = nextCost;
		FOR(i, 0, start.length()){
			int u = start[i] - 'a';
			int v = goal[i] - 'a';
			if(mps[u] == -1){
				mps[u] = v;
			}else{
				if(mps[u] != v) return -1;
			}
		}
		FOR(i, 0, 26){
			if(mps[i] != -1){
				A[++tot] = mk(i, mps[i]);
			}
		}
		if(tot == 26){
			int bb = 1;
			REP(x, 1, 26)
			REP(y, x + 1, 26) if(A[x].se == A[y].se) bb = 0;
			if(bb) return -1;
		}
		sort(A + 1, A + tot + 1);
		REP(i, 1, tot){
			work();
			A[1].fi += 26;
			sort(A + 1, A + tot + 1);
		}
		if(ans > 1e9) ans = -1;
		return ans;
	}
}stu;