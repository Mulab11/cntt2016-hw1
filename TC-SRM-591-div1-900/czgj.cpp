/*
	State-compressed dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MM = 299;
const int MOD = 1e9 + 9;
int a1[MM][MM], a2[MM][MM], (*F)[MM] = a1, (*G)[MM] = a2;
bool getb(int x, int p){
	if (p < 0) return 0;
	return x >> p & 1;
}
int setb(int x, int p, bool b = 1){
	return b ? x | 1 << p : x & ~(1 << p);
}
class StringPath {
	public:
	int countBoards(int n, int m, string A, string B) {
		if (A[0] != B[0]) return 0;
		memset(a1, 0, sizeof a1);
		memset(a2, 0, sizeof a2);
		int mm = (1 << m) - 1; F[1][1] = 1;
		// for each grid, getb(m1, j) == 1 <--> grid (i,j) is accessable with path A. 
		// So does m2 & B.
		rep(i, 0, n - 1) rep(j, 0, m - 1) if (i || j){ 
			rep(m1, 0, mm) rep(m2, 0, mm) G[m1][m2] = 0;
			rep(m1, 0, mm) rep(m2, 0, mm) if (F[m1][m2]){
				if (A[i + j] == B[i + j]){
					(G[setb(m1, j, getb(m1, j) || getb(m1, j - 1))][setb(m2, j, getb(m2, j) || getb(m2, j - 1))] += F[m1][m2]) %= MOD;
					(G[setb(m1, j, 0)][setb(m2, j, 0)] += (LL)25ll * F[m1][m2] % MOD) %= MOD;
				}
				else{
					(G[setb(m1, j, getb(m1, j) || getb(m1, j - 1))][setb(m2, j, 0)] += F[m1][m2]) %= MOD;
					(G[setb(m1, j, 0)][setb(m2, j, getb(m2, j) || getb(m2, j - 1))] += F[m1][m2]) %= MOD;
					(G[setb(m1, j, 0)][setb(m2, j, 0)] += (LL)24ll * F[m1][m2] % MOD) %= MOD;
				}
			} 
			swap(F, G);
		}
		int ret = 0;
		// fulfill getb(m1, m - 1) = getb(m2, m - 1) = 1
		rep(m1, 1 << m - 1, mm) rep(m2, 1 << m - 1, mm) ret = (ret + F[m1][m2]) % MOD;
		return ret;
	}
};

/*
	Iroaseru kokoro no kage wo
	Sotto daite kure masuka
		- Ito Hakanaki Hikari no Gotoku
*/
