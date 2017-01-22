/*
	Matrices, dp.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD = 1e9 + 7;
int c[255][255], d[255][255];
int id[20][20], p1[100], p2[100];
int n, cp1, cp2;
LL m;

struct matrix{
	int A[100][100], n, m;
	int* operator[](int x)const {
		return (int*)A[x];
	}
};
matrix P, ans, vec;
matrix _ret, __ret;
matrix operator *(const matrix& A, const matrix& B){
	memset(&_ret, 0, sizeof _ret);
	int n = _ret.n = A.n, m = A.m, o = _ret.m = m;
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
			for (int k = 0; k <= o; ++k){
				_ret[i][k] += (LL)A[i][j] * B[j][k] % MOD;
				if (_ret[i][k] >= MOD) _ret[i][k] -= MOD;
			}
	return _ret;
}
matrix pow(matrix A, LL n){
	memset(&__ret, 0, sizeof __ret);
	__ret.n = __ret.m = A.n;
	for (int i = 0; i <= __ret.n; ++i)
		__ret[i][i] = 1;
	for (LL i = 1; i <= n; i <<= 1, A = A * A)
		if (i & n) __ret = __ret * A;
	return __ret;
}

class ConversionMachine {
	public:
	int countAll(string word1, string word2, vector <int> costs, int maxCost) {
		// cost : c1 to c2
		c['a']['a'] = c['b']['b'] = c['c']['c'] = 0;
		c['a']['b'] = costs[0]; c['b']['c'] = costs[1]; c['c']['a'] = costs[2];
		c['a']['c'] = costs[0] + costs[1]; c['b']['a'] = costs[1] + costs[2]; c['c']['b'] = costs[2] + costs[0];
		
		// distance : c1 to c2
		d['a']['a'] = d['b']['b'] = d['c']['c'] = 0;
		d['a']['b'] = d['b']['c'] = d['c']['a'] = 1;
		d['a']['c'] = d['b']['a'] = d['c']['b'] = 2;
		
		LL mc = maxCost; // cost left
		n = word1.length(); m = cp1 = cp2 = 0;
		for (int i = 0; i < n; ++i){
			mc -= c[word1[i]][word2[i]];
			int tmp = d[word1[i]][word2[i]];
			m += tmp, cp1 += tmp == 1, cp2 += tmp == 2;
		}
		if (mc < 0) return 0;
		m += mc / ((LL)costs[0] + costs[1] + costs[2]) * 3 + 1;
		
		int cnt = 0;
		for (int i = 0; i <= n; ++i)
			for (int j = 0; i + j <= n; ++j)
				id[i][j] = ++cnt, p1[cnt] = i, p2[cnt] = j;
		
		// make the matrix
		memset(&P, 0, sizeof P); P.n = P.m = cnt;
		for (int i = 1; i <= cnt; ++i){
			int c1 = p1[i], c2 = p2[i], c0 = n - c1 - c2;
			P[id[c1][c2 + 1]][i] = c0;
			P[id[c1 - 1][c2]][i] = c1;
			P[id[c1 + 1][c2 - 1]][i] = c2;
		}
		// accumulator
		P[0][0] = P[0][1] = 1; 
		
		// initial vector
		memset(&vec, 0, sizeof vec); vec.n = cnt; vec.m = 0;
		vec[id[cp1][cp2]][0] = 1;
		
		return (pow(P, m) * vec)[0][0];
	}
};

/*
	'Kotae wa itsumo watashi no mune ni...'
		- Bouken desho desho
*/
