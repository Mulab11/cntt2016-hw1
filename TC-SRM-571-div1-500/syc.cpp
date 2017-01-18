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

int s[N];
int n, A[N], ans, m, ID[N];
bitset<55> G[N], suf[N];

int cmp(const int &a, const int &b){
	return A[a] > A[b];
}

void dfs(int x, int cho, int sum, bitset<55> now){
	int u = ID[x];
	int c = (now & suf[x]).count();
	if(cho + c < m) return;
	if(sum + A[u] * c <= ans) return;
	
	if(x > n){
		ans = sum;
		return;
	}
	
	if(now[u]) dfs(x + 1, cho + 1, sum + A[u], now & G[u]);
	dfs(x + 1, cho, sum, now);
}

struct MagicMolecule{
	int maxMagicPower(VI magicPower, vector<string> magicBond){
		n = magicPower.size();
		REP(i, 1, n) A[i] = magicPower[i - 1];
		REP(i, 1, n) ID[i] = i;
		sort(ID + 1, ID + n + 1, cmp);
		REP(i, 1, n) REP(j, 1, n) if(magicBond[i - 1][j - 1] == 'Y') G[i][j] = 1;
		REP(i, 1, n) G[0][i] = 1;
		REP(i, 1, n) s[i] = s[i - 1] + A[ID[i]];
		REP(i, 1, n) REP(j, i, n) suf[i][ID[j]] = 1;
		for(m = 1; 3 * m < 2 * n; m ++);
		ans = -1;
		dfs(1, 0, 0, G[0]);
		return ans;
	}
}stu;