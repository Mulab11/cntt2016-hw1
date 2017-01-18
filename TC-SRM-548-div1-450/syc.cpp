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

int missing;
set<PII> st;
bitset<2505> dp[105][55];

struct KingdomAndDice{
	db newFairness(VI firstDie, VI secondDie, int X){
		for(auto v : firstDie){
			if(!v) missing ++;
			else st.insert(mk(v, 0));
		}
		for(auto v : secondDie) st.insert(mk(v, 1));
		int x = st.begin()->fi;
		FOR(i, 0, min(x, missing + 1)) dp[0][i][0] = 1;
		int sum = 0;
		int stp = 0;
		int ori = 0;
		st.insert(mk(X + 1, -1));
		for(set<PII> :: iterator it = st.begin(), vv; it != st.end(); it ++){
			stp ++;
			if(it -> se == 1) sum ++;
			if(it -> se == 0) ori += sum;
			vv = it;
			vv ++;
			int most = vv -> fi - it -> fi - 1;
			REP(j, 0, missing)
			REP(k, 0, j){
				if(k > most) break;
				dp[stp][j] |= dp[stp - 1][j - k] << (sum * k);
			}
			if(vv -> se == -1) break;
		}
		int SZ = firstDie.size();
		SZ *= SZ;
		db ans = 1e30;
		REP(i, 0, 2500){
			int ok = 0;
			REP(x, 0, missing)  ok |= dp[stp][x][i];
			if(ok){
				db prb = 1.0 * (i + ori) / SZ;
				if(fabs(prb - 0.5) - fabs(ans - 0.5) < -1e-7) ans = prb;
			}
		}
		return ans;
	}
} stu;