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

int n, m, cnt;
int id[55][55];
VI adj[2555];

int dx[6] = {-1, -1, 0, 0, 1, 1};
int dy[6] = {0, 1, -1, 1, -1, 0};
int col[2555];

struct HexagonalBoard{
	
	int dfs(int x, int y){
		if(col[x] == -1){
			col[x] = y;
		}else{
			if(y != col[x]) return 0;
			return 1;
		}
		for(auto v : adj[x]) if(!dfs(v, y ^ 1)) return 0;
		return 1;
	}
	
	int minColors(vector<string> board){
		n = board.size();
		m = board[0].size();
		FOR(i, 0, n) FOR(j, 0, m) if(board[i][j] == 'X') id[i][j] = ++cnt;
		FOR(i, 0, n) FOR(j, 0, m)if(board[i][j] == 'X'){
			FOR(k, 0, 6){
				int nx = i + dx[k];
				int ny = j + dy[k];
				if(nx < 0 || nx >= n || ny < 0 || ny >= m || board[nx][ny] == '-') continue;
				adj[id[i][j]].pb(id[nx][ny]);
			}
		}
		
		if(!cnt) return 0;
		
		memset(col, -1, sizeof col);
		
		int flag = 1;
		REP(i, 1, cnt) if(adj[i].size()) flag = 0;
		if(flag) return 1;
		
		REP(i, 1, cnt) if(col[i] == -1){
			if(!dfs(i, 0)) return 3;
		}
		return 2;
	}
};