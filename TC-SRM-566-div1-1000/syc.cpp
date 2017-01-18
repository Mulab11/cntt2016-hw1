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
typedef long long ll;
typedef vector<int> VI;
typedef vector<VI > VII;
typedef PR<int,int> PII;
typedef vector<PII> VPI;
const	int inf=2e9;
const	ll Inf=1e10;
const	int P=1e5+7;
const	int N=255;
const	db pi = acos(-1);

inline ll IN(){
	ll x = 0;
	int ch = 0, f = 0;
	for (CH; ch != -1 && (ch < 48 || ch > 57); CH) f = (ch == '-');
	for (; ch >= 48 && ch <= 57; CH) x = (x << 1) + (x << 3) + ch - '0';
	return f ? (-x) : x;
}
template<typename T> inline int chkmin(T &a, const T &b){if(b < a) return a = b, 1; return 0;}
template<typename T> inline int chkmax(T &a, const T &b){if(b > a) return a = b, 1; return 0;}

void renew(int &x, const int &y){
	if((x += y) >= P) x -= P;
}

int n, m, c;
int color[N];
int valid[N][N], H[N][N][2], G[N][N], F[N][N];
ll col[N][N], pts[N][N];
db dx[N], dy[N];

struct FencingPenguins{
	int countWays(int numPosts, int radius, vector<int> ix, vector<int> iy, string icolor){
		n = numPosts;
		FOR(i, 0, n){
			dx[i] = radius * cos(2 * pi * i / n);
			dy[i] = radius * sin(2 * pi * i / n);
		}
		m = ix.size();
		FOR(i, 0, m){
			if(!color[(int)icolor[i]]) color[(int)icolor[i]] = ++c;
		}
		FOR(i, 0, n)
		FOR(j, 0, n){
			if(i == j) continue;
			FOR(k, 0, m){
				int tx = ix[k], ty = iy[k];
				if(1ll * (dx[j] - dx[i]) * (ty - dy[i]) - 1ll * (dy[j] - dy[i]) * (tx - dx[i]) > 0){
					col[i][j] |= 1LL << color[(int)icolor[k]];
					pts[i][j] |= 1LL << k;
				}
			}
		}
		FOR(i, 0, n) if(pts[i][(i - 1 + n) % n]) return 0;
		FOR(i, 0, n) FOR(j, 0, n) if(i != j) valid[i][j] = ( col[i][j] & col[j][i] ) == 0;
		FOR(i, 0, n) H[i][i][0] = 1;
		FOR(len, 1, n){
			if(len == 2)
				len = 2;
			FOR(l, 0, n - len){
				int r = l + len;
				REP(x, 0, 1){
					int ans = 0;
					REP(y, l + 1, r){
						if(!valid[l][y]) continue;
						ll now = pts[l][y] & pts[y][r] & pts[r][l]; int has = bool(now);
						int gt = 0;
						REP(phas, 0, 1){
							if((phas | has) != x) continue;
							renew(gt, H[y][r][phas]);
						}
						if(!pts[y][l]){
							renew(ans, gt);
						}else{
							if((y - l >= 4) && ((pts[y][l] & pts[l + 1][y - 1]) == 0)){
								renew(ans, 1ll * gt * F[l + 1][y - 1] % P);
							}
						}
					}
					H[l][r][x] = ans;
				}
				int ans = 0;
				REP(x, l + 2, r){
					if(!valid[l][x]) continue;
					int gt = H[l][x][1];
					if(!(pts[l][x] & pts[r][l])){
						renew(ans, gt);
					}else{
						if(r - x >= 3 && !(pts[l][x] & pts[x + 1][r] & pts[r][l])){
							renew(ans, 1ll * gt * F[x + 1][r] % P);
						}
					}
				}
				G[l][r] = ans;
				ans = 0;
				FOR(x, l, r) if(!(pts[x][r] & pts[r][l])) renew(ans, G[x][r]);
				F[l][r] = ans;
			}
		}
		return F[0][n - 1];
	}
} stu;