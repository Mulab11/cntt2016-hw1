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
const	int N=45;

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

int n, m, r;
char mps[N][N];
bool vis[N][N][N][N];
struct node{
	int x1, y1;
	int x2, y2;
}Q[N * N * N * N / 2];
int ID[N][N];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int xx[2], yy[2], tx[2], ty[2];
int fa[N * N], p2[N * N];
struct CoinsGame{
	
	int get(int x){
		if(fa[x] == x) return x;
		return fa[x] = get(fa[x]);
	}
	
	int ways(vector<string> board){
		n = board.size();
		m = board[0].size();
		REP(i, 1, n)
		REP(j, 1, m) mps[i][j] = board[i - 1][j - 1];
		
		REP(x1, 0, n + 1)
		REP(y1, 0, m + 1){
			if(1 <= x1 && x1 <= n && 1 <= y1 && y1 <= m) continue;
			REP(x2, 1, n)
			REP(y2, 1, m){
				if(mps[x2][y2] == '#') continue;
				if(!vis[x1][y1][x2][y2]){
					vis[x1][y1][x2][y2] = vis[x2][y2][x1][y1] = 1;
					Q[++r] = (node){x1, y1, x2, y2};
				}
			}
		}
		
		REP(l, 1, r){
			xx[0] = Q[l].x1; yy[0] = Q[l].y1;
			xx[1] = Q[l].x2; yy[1] = Q[l].y2;
			tx[0] = tx[1] = ty[0] = ty[1] = 0;
			REP(d, 0, 3){
				REP(s, 1, 3){
					int ok = 1;
					REP(c, 0, 1){
						if((s >> c) & 1){
							int nx = xx[c] + dx[d];
							int ny = yy[c] + dy[d];
							if(nx < 1 || nx > n || ny < 1 || ny > m){
								ok = 0;
								break;
							}
							if(mps[nx][ny] != '.'){
								ok = 0;
								break;
							}
							tx[c] = nx;
							ty[c] = ny;
						}else{
							int nx = xx[c] - dx[d];
							int ny = yy[c] - dy[d];
							if(nx < 1 || nx > n || ny < 1 || ny > m){
								ok = 0;
								break;
							}
							if(mps[nx][ny] != '#'){
								ok = 0;
								break;
							}
							tx[c] = xx[c];
							ty[c] = yy[c];
						}
					}
					
					if(ok){
						if(!vis[tx[0]][ty[0]][tx[1]][ty[1]]){
							vis[tx[0]][ty[0]][tx[1]][ty[1]] = 1;
							vis[tx[1]][ty[1]][tx[0]][ty[0]] = 1;
							Q[++r] = (node){tx[0], ty[0], tx[1], ty[1]};
						}
					}
				}
			}
		}
		
		int cnt = 0;
		REP(i, 1, n) REP(j, 1, m) if(mps[i][j] == '.') ID[i][j] = ++cnt;
		REP(i, 1, cnt) fa[i] = i;
		REP(i, 1, n) REP(j, 1, m)
		REP(ii, 1, n) REP(jj, 1, m) if(ID[i][j] && ID[ii][jj] && !vis[i][j][ii][jj]){
			int u = get(ID[i][j]);
			int v = get(ID[ii][jj]);
			fa[u] = v;
		}
		
		p2[0] = 1;
		REP(i, 1, cnt) p2[i] = (p2[i - 1] << 1) % P;
		
		int res = p2[cnt] - 1;
		REP(i, 1, cnt) if(get(i) == i){
			int sz = 0;
			REP(j, 1, cnt) if(get(j) == i) ++sz;
			res = (res + P - (p2[sz] - 1)) % P;
		}
		return res;
	}
}stu;