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

int n;
LL D[N][N];
int al[N], tot, vis[N][N];
struct SkiResorts{
	LL minCost(vector<string> road, VI altitude){
		n = altitude.size();
		REP(i, 1, n) al[i] = altitude[i - 1];
		sort(al + 1, al + n + 1);
		tot = unique(al + 1, al + n + 1) - (al + 1);
		REP(i, 1, n) REP(j, 1, tot) D[i][j] = 1LL << 60;
		REP(i, 1, tot) D[1][i] = abs(altitude[0] - al[i]);
		while(1){
			int p = -1, vx = -1, vy = -1;
			REP(i, 1, n) REP(j, 1, tot){
				if(!vis[i][j] && (p == -1 || D[i][j] < D[vx][vy])){
					vx = i;
					vy = j;
					p = 1;
				}
			}
			if(p == -1) break;
			vis[vx][vy] = 1;
			REP(ii, 1, n) if(road[vx - 1][ii - 1] == 'Y') REP(j, 1, vy){
				if(D[vx][vy] + abs(altitude[ii - 1] - al[j]) < D[ii][j]){
					D[ii][j] = D[vx][vy] + abs(altitude[ii - 1] - al[j]);
				}
			}
		}
		
		LL ans = 1LL << 60;
		REP(i, 1, tot) chkmin(ans, D[n][i]);
		if(ans > (1LL << 59)) return -1;
		return ans;
	}
};