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

db ans;
db A[N * N];
int siz;
int n, m, K, cnt;
int ID[N][N], DD[N * N];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
char mps[N][N];
VI adj[N * N];
int fa[N * N], ver;
int sz[N * N], rt;
int dis[305][305], I2[N * N];
struct Orienteering{
	void dfs(int x){
		sz[x] = DD[x];
		for(auto v : adj[x]){
			if(v == fa[x]) continue;
			fa[v] = x;
			dfs(v);
			sz[x] += sz[v];
		}
		ans += 2 * (1 - A[sz[x]] - A[siz - sz[x]]);
	}
	
	void DFS(int x, int f, int pre){
		if(I2[x]) dis[rt][I2[x]] = f;
		for(auto v : adj[x]){
			if(v == pre) continue;
			DFS(v, f + 1, x);
		}
	}
	
	db expectedLength(vector<string> field, int K){
		::K = K;
		n = field.size();
		n = field.size();
		m = field[0].size();
		REP(i, 1, n) REP(j, 1, m) mps[i][j] = field[i - 1][j - 1];
		REP(i, 1, n) REP(j, 1, m) if(mps[i][j] != '#'){
			ID[i][j] = ++cnt;
			if(mps[i][j] == '*'){
				DD[cnt] = 1;
			}
		}
		REP(i, 1, n) REP(j, 1, m){
			if(mps[i][j] == '*') ++siz;
			REP(k, 0, 3){
				int ii = i + dx[k];
				int jj = j + dy[k];
				if(ii < 1 || ii > n || jj < 1 || jj > m) continue;
				if(mps[ii][jj] == '#') continue;
				adj[ID[i][j]].pb(ID[ii][jj]);
			}
		}
		
		REP(i, 1, cnt) if(DD[i]) I2[i] = ++ver;
		REP(i, K, ver){
			A[i] = 1;
			FOR(j, 0, K) A[i] *= 1.0 * (i - j) / (ver - j);
		}	
		dfs(1);
		REP(i, 1, cnt) if(DD[i]){
			rt = I2[i];
			DFS(i, 0, -1);
		}
		
		memset(A, 0, sizeof A);
		REP(i, K - 2, ver){
			A[i] = 1;
			FOR(j, 0, K - 2) A[i] *= 1.0 * (i - j) / (ver - 2 - j);
			A[i] *= 1.0 * K / ver * (K - 1) / (ver - 1);
		}
		
		REP(i, 1, ver)
		REP(j, i + 1, ver){
			int cnt = 0;
			REP(k, 1, ver) if(k != i && k != j){
				if(dis[k][i] > dis[i][j]) continue;
				if(dis[k][j] > dis[i][j]) continue;
				if(dis[k][i] == dis[i][j] && k < j) continue;
				if(dis[k][j] == dis[i][j] && k < i) continue;
				++cnt;
			}
			ans -= A[cnt] * dis[i][j];
		}
		
		return ans;
	}
}stu;