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
const	int inf=1e9;
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

int n, m, c;
int all[N];
int vis[N][N];
int ta[N][N], fr[N][N];
int qx[N * N], qy[N * N], r;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
char frame[N][N];
struct Tunnels{

	void bfs(int x, int y){
		++c;
		vis[qx[r = 1] = x][qy[1] = y] = 1;
		int ymin = 1 << 30, ymax = -1 << 30;
		int xmin = 1 << 30, xmax = -1 << 30, cnt = 0;
		REP(l, 1, r){
			int ux = qx[l], uy = qy[l];
			chkmin(xmin, ux);
			chkmax(xmax, ux);
			FOR(k, 0, 4){
				int vx = ux + dx[k];
				int vy = uy + dy[k];
				if(vx < 1 || vx > n || vy < 1 || vy > m || frame[vx][vy] == '.' || vis[vx][vy]) continue;
				++r;
				vis[qx[r] = vx][qy[r] = vy] = 1;
			}
		}
		if(r == 1){
			fr[qx[1]][qy[1]] = 1;
			if(qx[1] == 1 && (qy[1] == 1 || qy[1] == m)) ta[qx[1]][qy[1]] = 1;
			return;
		}
		if(xmin != xmax){
			cnt = 0, ymin = 1 << 30, ymax = -ymin;
			REP(l, 1, r) if(qx[l] == xmin){
				chkmin(ymin, qy[l]);
				chkmax(ymax, qy[l]);
				++cnt;
			}
			if(cnt == 1){
				REP(l, 1, r) if(qx[l] == xmin) fr[qx[l]][qy[l]] = 1;
			}else{
				REP(l, 1, r){
					int x = qx[l], y = qy[l];
					if(x == xmin && frame[x + 1][y] == '.' && (y == ymax || y == ymin)) fr[x][y] = 1;
				}
			}
			if(r == 2 && xmin != 1) return;
			ymin = 1 << 30;
			ymax = -ymin;
			cnt = 0;
			REP(l, 1, r) if(qx[l] == xmax){
				chkmin(ymin, qy[l]);
				chkmax(ymax, qy[l]);
				++cnt;
			}
			if(cnt == 1){
				REP(l, 1, r) if(qx[l] == xmax) ta[qx[l]][qy[l]] = 1;
			}else{
				REP(l, 1, r){
					int x = qx[l], y = qy[l];
					if(x == xmax && frame[x - 1][y] == '.' && (y == ymax || y == ymin)) ta[x][y] = 1;
				}
			}
		}else{
			ymin = 1 << 30;
			ymax = -ymin;
			REP(l, 1, r){
				chkmin(ymin, qy[l]);
				chkmax(ymax, qy[l]);
			}
			if(r == m){
				all[xmin] = 1;
				return;
			}else{
				if(xmin == 1){
					if(ymin == 1){
						REP(l, 1, r){
							if(qy[l] == ymax) fr[qx[l]][qy[l]] = 1;
							if(qy[l] == ymin) ta[qx[l]][qy[l]] = 1;
						}
					}else
					if(ymax == m){
						REP(l, 1, r){
							if(qy[l] == ymin) fr[qx[l]][qy[l]] = 1;
							if(qy[l] == ymax) ta[qx[l]][qy[l]] = 1;
						}
					}else{
						REP(l, 1, r){
							if(qy[l] == ymin) fr[qx[l]][qy[l]] = 1;
						}
					}
				}else{
					if(ymin == 1){
						REP(l, 1, r) if(qy[l] == ymin) fr[qx[l]][qy[l]] = 1;
					}else
					if(ymax == m){
						REP(l, 1, r) if(qy[l] == ymax) fr[qx[l]][qy[l]] = 1;
					}
				}
			}
		}
	}

	int dp[55][55][55];
	int Main(){
		memset(dp, 0x3f, sizeof dp);
		if(all[1]){
			dp[1][1][0] = 1;
			dp[1][0][1] = 1;
		}else{
			int cnt = 0;
			REP(i, 1, m) if(fr[1][i]) ++cnt;
			dp[1][ta[1][1]][ta[1][m]] = cnt;
		}

		REP(i, 2, n) REP(l, 0, n) REP(r, 0, n){
			int val = dp[i - 1][l][r];
			if(val >= inf) continue;
			if(all[i]){
				if(l) chkmin(dp[i][l - 1][r + 1], val);
				else chkmin(dp[i][l][r + 1], val + 1);
				if(r) chkmin(dp[i][l + 1][r - 1], val);
				else chkmin(dp[i][l + 1][r], val + 1);
			}else{
				int cst = 0;
				int nl = l, nr = r;
				if(fr[i][1]){
					if(!l) cst ++, nl = 0;
					else nl = l - 1;
				}else
				if(ta[i][1]){
					nl = l + 1;
				}
				if(fr[i][m]){
					if(!r) cst ++, nr = 0;
					else nr = r - 1;
				}else
				if(ta[i][m]){
					nr = r + 1;
				}
				chkmin(dp[i][nl][nr], cst + val);
			}
		}

		int ans = 1 << 30;
		REP(i, 0, n) REP(j, 0, n) chkmin(ans, dp[n][i][j]);
		return ans;
	}


	int minimumTunnels(vector<string> frame){
		n = frame.size();
		m = frame[0].size();
		if(m == 1){
			int has = 0;
			FOR(i, 0, n) FOR(j, 0, m) if(frame[i][j] == 'X') has = 1;
			return has;
		}
		FOR(i, 0, n) FOR(j, 0, m) ::frame[i + 1][j + 1] = frame[i][j];
		REP(i, 1, n) REP(j, 1, m) if(!vis[i][j] && ::frame[i][j] == 'X') bfs(i, j);
		return Main();
	}
}stu;