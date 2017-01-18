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

int n, sum;
int f[1 << 12][131];
struct KeyDungeonDiv1{
	int maxKeys(VI dR, VI dG, VI R, VI G, VI W, VI keys){
		memset(f, -1, sizeof f);
		n = W.size();
		f[0][keys[0]] = keys[2];
		int ans = 0;
		for(int i = 0; i < (1 << n); i ++)
		for(int j = 0; j <= 130; j ++) if(f[i][j] != -1){
			int nr = j;
			int nw = f[i][j];
			int ng = keys[0] + keys[1] + keys[2];
			for(int k = 0; k < n; k ++) if((i >> k) & 1) ng += R[k] + G[k] + W[k] - dR[k] - dG[k];
			ng -= nr + nw;
			chkmax(ans, nr + nw + ng);
			for(int k = 0; k < n; k ++) if(!((i >> k) & 1)){
				int wr = max(0, dR[k] - nr);
				int wg = max(0, dG[k] - ng);
				if(wr + wg <= nw){
					int new_r = max(0, nr - dR[k]) + R[k];
					int new_w = nw - wr - wg + W[k];
					chkmax(f[i | (1 << k)][new_r], new_w);
				}
			}
		}
		return ans;
	}
}s;