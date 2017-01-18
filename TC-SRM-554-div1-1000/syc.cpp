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
const	int P=1234567891;
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
	LL u = 0LL + x + y;
	if(u >= P) u -= P;
	if(u <  0) u += P;
	x = u;
}

int Pow(int x, int y, int p){
	int a = 1;
	for (; y; y >>= 1, x = (LL)x * x %p) if(y & 1) a=(LL)a * x%p;
	return a;
}

int f[55];
int A[55][55], B[55], cnt;
int res[55];
int id[55][55], vv;
int g1[55], g2[55], bb[55], col;
struct mat{
	int v[205][205];
}tmp, e, ans;

mat operator *(const mat &a, const mat &b){
	REP(i, 1, vv) REP(j, 1, vv){
		tmp.v[i][j] = 0;
		REP(k, 1, vv) tmp.v[i][j] = (tmp.v[i][j] + 1LL * a.v[i][k] * b.v[k][j]) % P;
	}
	return tmp;
}

int vt[55], cc;
class TheBrickTowerHardDivOne{
	public:
		void dfs(int x){
			//1 2
			//3 4
			if(x == 5){
				++cnt;
				REP(i, 1, 4) A[cnt][i] = f[i];
				if(f[1] == f[2]) B[cnt] ++;
				if(f[1] == f[3]) B[cnt] ++;
				if(f[2] == f[4]) B[cnt] ++;
				if(f[3] == f[4]) B[cnt] ++;
				return;
			}
			REP(i, 1, x){
				if(x == i || f[i] == i){
					f[x] = i;
					dfs(x + 1);
					f[x] = 0;
				}
			}
		}
		
		void DFS(int x){
			if(x == 5){
				REP(i, 1, 4)
				REP(j, 1, 4) if(g2[i] != g2[j] && bb[g2[i]] == bb[g2[j]]) return;
				
				int nw = 1, sm = 0, pp = col;
				REP(i, 1, 4) if(g1[i] == i) pp --;
				pp = max(pp, 0);
				REP(i, 1, 4) if(g2[i] == i && bb[i] == i + 4){
					nw = 1LL * nw * pp % P;
					pp = max(pp - 1, 0);
				}
				if(bb[g2[1]] == g1[1]) ++sm;
				if(bb[g2[2]] == g1[2]) ++sm;
				if(bb[g2[3]] == g1[3]) ++sm;
				if(bb[g2[4]] == g1[4]) ++sm;
				if(bb[g2[1]] == bb[g2[2]]) ++sm;
				if(bb[g2[1]] == bb[g2[3]]) ++sm;
				if(bb[g2[2]] == bb[g2[4]]) ++sm;
				if(bb[g2[3]] == bb[g2[4]]) ++sm;
				renew(res[sm], nw);
				return;
			}
			if(g2[x] != x){
				bb[x] = bb[g2[x]];
				DFS(x + 1);
				return;
			}
			bb[x] = x + 4;
			DFS(x + 1);
			REP(i, 1, 4) if(g1[i] == i){
				bb[x] = i;
				DFS(x + 1);
			}
			bb[x] = 0;
		}
		
		int find(int C, int K, LL H){
			memset(f, 0, sizeof f);
			memset(A, 0, sizeof A);
			memset(B, 0, sizeof B);
			col = C;
			f[1] = 1;
			dfs(2);
			
			REP(i, 1, cnt) REP(j, 0, K) id[i][j] = ++vv;
			
			REP(i, 1, cnt)
			REP(j, 1, cnt){
				if(B[i] > K || B[j] > K) continue;
				memset(bb, 0, sizeof bb);
				memset(res, 0, sizeof res);
				REP(a, 1, 4) g1[a] = A[i][a];
				REP(a, 1, 4) g2[a] = A[j][a];
				DFS(1);
								
				
				REP(x, 0, K)
				REP(y, 0, K - x){
					renew(e.v[id[i][x]][id[j][x + y]], res[y]);
					renew(e.v[id[i][x]][vv + 1], res[y]);
				}
			}
			++vv;
			e.v[vv][vv] = 1;
			
			REP(i, 1, cnt) if(B[i] <= K){
				int nw = 1, pp = col;
				REP(x, 1, 4) if(A[i][x] == x) nw = 1LL * nw * pp % P, pp = max(0, pp - 1);
				ans.v[1][id[i][B[i]]] = nw;
				renew(ans.v[1][vv], nw);
			}
			
			for(H --; H; H >>= 1, e = e * e) if(H & 1) ans = ans * e;
			
			return ans.v[1][vv];
		}
}cla;