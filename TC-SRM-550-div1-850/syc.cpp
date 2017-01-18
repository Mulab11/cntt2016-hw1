#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <bitset>
#include <vector>
#include <string>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define REP(i, x, y)  for(int i = (int)x; i <= (int)y; i ++)
#define FOR(i, x, y)  for(int i = (int)x; i <  (int)y; i ++)
#define PER(i, x, y)  for(int i = (int)x; i >= (int)y; i --)
#define fi first
#define se second
#define pb push_back
#define mk make_pair
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int, int> PII;
const	int N = 105;
const	int inf = 1e9;
const	ll Inf = 1e16;
const	int P = (int)1e9 + 7;

int opt[N], fac[N];
int n, c0, c1, c2, M, id[N][N], cnt, pans;
char S[N], T[N];

struct mat{
	int v[N][N];
	mat operator *(const mat &a)const{
		mat c;
		memset(c.v, 0, sizeof c.v);
		REP(i, 1, cnt) REP(j, 1, cnt){
			REP(k, 1, cnt) c.v[i][j] = (c.v[i][j] + 1ll * v[i][k] * a.v[k][j]) % P;
		}
		return c;
	}
}e, ans;

int f[5];

int Main(){
	n = strlen(S + 1);
	int stp = 0;
	REP(i, 1, n){
		char u = S[i], v = T[i];
		int nowstp = 0;
		while(u != v){
			nowstp ++;
			if(u == 'a'){
				u = 'b';
				M -= c0;
			}else
			if(u == 'b'){
				u = 'c';
				M -= c1;
			}else
			if(u == 'c'){
				u = 'a';
				M -= c2;
			}
			if(M < 0){
				puts("0");
				return 0;
			}
		}
		f[nowstp] ++;
		stp += nowstp;
	}
	M /= (c0 + c1 + c2); M *= 3; stp += M;
	pans = ++cnt;
	REP(i, 0, n) REP(j, 0, n - i) id[i][j] = ++cnt;
	int g = id[n][0], nw = id[f[0]][f[1]];
	ans.v[1][nw] = 1;
	if(nw == g) ans.v[1][pans] = 1;
	REP(i, 0, n) REP(j, 0, n - i){
		int u = id[i][j];
		if(i){
			int v = id[i - 1][j];
			if(v == g){
//				fprintf(stderr, "%d %d\n", i, j);
				e.v[u][pans] += i;
			}
			e.v[u][v] += i;
		}
		if(j){
			int v = id[i + 1][j - 1];
			if(v == g){
//				fprintf(stderr, "%d %d\n", i, j);
				e.v[u][pans] += j;
			}
			e.v[u][v] += j;
		}
		if(i + j < n){
			int v = id[i][j + 1];
			if(v == g){
//				fprintf(stderr, "%d %d\n", i, j);
				e.v[u][pans] += n - i - j;
			}
			e.v[u][v] += n - i - j;
		}
	}
	e.v[pans][pans] ++;
	for(; stp; stp >>= 1){
		if(stp & 1){
			ans = ans * e;
		}
		e = e * e;
	}
	return ans.v[1][pans];
}


struct ConversionMachine{
	int countAll(string word1, string word2, vector<int> Cost, int mCost){
		FOR(i, 0, word1.length()) S[i + 1] = word1[i];
		FOR(i, 0, word2.length()) T[i + 1] = word2[i];
		c0 = Cost[0];
		c1 = Cost[1];
		c2 = Cost[2];
		M = mCost;
		
		return Main();
	}
};