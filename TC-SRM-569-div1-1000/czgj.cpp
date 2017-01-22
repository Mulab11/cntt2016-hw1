/*
	matrice
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 63;
int n, m, k;
LL MOD;
struct matrix{
	LL a[MAXN][MAXN];
	matrix(bool v = 0){
		memset(a, 0, sizeof a);
		if (v) rep(i, 0, n) a[i][i] = 1;
	}
	LL * operator[](int x) const{
		return (LL*)a[x];
	}
};
matrix operator *(const matrix& a, const matrix& b){
	static matrix c; c = matrix(0);
	rep(i, 0, n) rep(j, 0, n) rep(k, 0, n) c[i][k] = (c[i][k] + a[i][j] * b[j][k]) % MOD;
	return c;
}
matrix power(const matrix& a, LL k){
	static matrix c, d; c = matrix(1); d = a;
	for (; k; k >>= 1, d = d * d)
		if (k & 1) c = c * d;
	return c;
}
matrix mat[MAXN];
LL powp[MAXN];
class MegaFactorial {
	public:
	int countTrailingZeros(int N, int K, int B) {
		int p = vector<int>{0, 0, 2, 3, 2, 5, 3, 7, 2, 3, 5}[B]; // the prime base
		int c = vector<int>{0, 0, 1, 1, 2, 1, 1, 1, 3, 2, 1}[B]; // index / c
		MOD = (1e9 + 9) * c;
		n = K; m = N;
		int mxid = 0; // max index
		for (LL i = 1; i <= m; i *= p, ++mxid) powp[mxid] = i; 
		--mxid;
		mat[0][0][0] = 1;
		rep(i, 1, n) rep(j, i, n) mat[0][i][j] = 1;
		rep(i, 1, mxid){ // make matrice
			mat[i] = power(mat[i - 1], p);
			rep(j, 1, n) mat[i][0][j] = (mat[i][0][j] + 1) % MOD;
		}
		matrix A(1);
		red(i, mxid, 0){ // quick power in p-base
			LL t = m / powp[i];
			if (t) A = A * power(mat[i], t);
			m %= powp[i];
		}
		return A[0][n] / c;
	}
};

/*
	chikoku....
*/
