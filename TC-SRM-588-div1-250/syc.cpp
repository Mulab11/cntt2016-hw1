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

int n, ID[N];
int F[N][N];
struct GUMIAndSongsDiv1{	
	int maxSongs(VI du, VI to, int T){
		n = du.size();
		FOR(i, 0, n) ID[i] = i;
		sort(ID, ID + n, [&](const int &a, const int &b){return to[a] < to[b];});
		memset(F, 0x3f, sizeof F);
		F[0][0] = 0;
		F[0][1] = du[ID[0]];
		FOR(i, 1, n){
			F[i][1] = du[ID[i]];
			REP(j, 2, i + 1){
				FOR(k, 0, i){
					chkmin(F[i][j], F[k][j - 1] + to[ID[i]] - to[ID[k]] + du[ID[i]]);
				}
			}
		}
		int ans = 0;
		while(ans <= n){
			int flag = 0;
			FOR(i, 0, n) if(F[i][ans] <= T) flag = 1;
			if(!flag) break;
			ans ++;
		}
		return ans - 1;
	}
}s;