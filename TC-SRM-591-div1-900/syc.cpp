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

struct node{
	int x, y, z;
	node(){}
	node(int xx, int yy, int zz){
		x = xx;
		y = yy;
		z = zz;
	}
};

int n, m;
string A, B;
int dp[10][10][1 << 17];
int Aftx[10][10];
int Afty[10][10];
int len[10][10];
node V[10][10][20];

int mskA[10][10], mskB[10][10];
void decode(int x, int y, int S){
	PER(i, len[x][y], 1){
		int u = V[x][y][i].x;
		int v = V[x][y][i].y;
		int w = V[x][y][i].z;
		int t = S & 1;
		if(!w){
			mskA[u][v] = t;
		}else{
			mskB[u][v] = t;
		}
		S >>= 1;
	}
}

int encode(int x, int y){
	int msk = 0;
	REP(i, 1, len[x][y]){
		msk <<= 1;
		int u = V[x][y][i].x;
		int v = V[x][y][i].y;
		int w = V[x][y][i].z;
		if(!w){
			msk |= mskA[u][v];
		}else{
			msk |= mskB[u][v];
		}
	}
	return msk;
}

struct StringPath{
	
	int dfs(int x, int y, int S){
		if(x == 0 && y == 0) return dfs(Aftx[0][0], Afty[0][0], 3);
		if(x == n - 1 && y == m - 1){
			decode(x, y, S);
			return ((x && mskA[x - 1][y]) || (y && mskA[x][y - 1])) && ((x && mskB[x - 1][y]) || (y && mskB[x][y - 1]));
		}
		int &res = dp[x][y][S];
		if(res != -1) return res;
		res = 0;

		int trs[5];
		int now = x + y;
		int nx = Aftx[x][y];
		int ny = Afty[x][y];
		int bid = -1, tot = 0;

		decode(x, y, S);
		REP(c, 'A', 'Z'){
			if(c != A[now] && c != B[now]){
				if(bid != -1) continue;
				mskA[x][y] = 0;
				mskB[x][y] = 0;
				bid = encode(nx, ny);
			}else{
				mskA[x][y] = (c == A[now]) && ((x && mskA[x - 1][y]) | (y && mskA[x][y - 1]));
				mskB[x][y] = (c == B[now]) && ((x && mskB[x - 1][y]) | (y && mskB[x][y - 1]));
				trs[++tot] = encode(nx, ny);
			}
		}
		
		REP(i, 1, tot) renew(res, dfs(nx, ny, trs[i]));
		renew(res, 1LL * (26 - tot) * dfs(nx, ny, bid) % P);
		return res;
	}
	
	int countBoards(int n, int m, string A, string B){
		if(n > m) swap(n, m);
		::n = n;
		::m = m;
		::A = A;
		::B = B;
		if(A[0] != B[0]) return 0;
		if(A[n + m - 2] != B[n + m - 2]) return 0;
		
		memset(dp, -1, sizeof dp);
		
		FOR(i, 0, n) FOR(j, 0, m) {
			Aftx[i][j] = i + 1;
			Afty[i][j] = j - 1;
			if(Aftx[i][j] >= n || Afty[i][j] < 0){
				Aftx[i][j] = 0;
				Afty[i][j] = i + j + 1;
				while(Afty[i][j] >= m){
					Afty[i][j] --;
					Aftx[i][j] ++;
				}
			}
			
			int bit = 0;
			FOR(jj, 0, m) FOR(ii, 0, n) if(ii + jj == i + j - 1 && jj <= j){
				V[i][j][++bit] = node(ii, jj, 0);
				V[i][j][++bit] = node(ii, jj, 1);
			}
			FOR(jj, 0, m) FOR(ii, 0, n) if(ii + jj == i + j && jj > j){
				V[i][j][++bit] = node(ii, jj, 0);
				V[i][j][++bit] = node(ii, jj, 1);
			}
			len[i][j] = bit;
		}
		
		return dfs(0, 0, 0);
	}
}s;