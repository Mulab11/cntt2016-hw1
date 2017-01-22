/*
	matrix-tree
	inclusion-exclusion
	meet in the middle
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD = 1e9 + 7;
const int MAXN = 50;

LL F[MAXN];
struct Matrix{
	LL A[MAXN][MAXN], sz;
	LL* operator[](int x)const{
		return (LL*)A[x];
	}
};
LL pow(LL x, LL y){
	LL ret = 1;
	for (LL i = 1; i <= y; i <<= 1, x = x * x % MOD)
		if (i & y) ret = ret * x % MOD;
	return ret;
}
LL inv(LL x){
	return pow(x, MOD - 2);
}
LL det(const Matrix& A){
	LL ret = 1; int n = A.sz;
	for (int i = 1; i <= n; ++i){
		int ti = -1;
		for (ti = i; ti <= n; ++ti)
			if (A[ti][i]) break;
		if (ti > n) return 0;
		if (ti != i){
			ret = -ret;
			for (int j = i; j <= n; ++j)
				swap(A[i][j], A[ti][j]);
		}
		ret = ret * A[i][i] % MOD;
		LL pi = inv(A[i][i]);
		for (int j = i + 1; j <= n; ++j){
			LL t = A[j][i] * pi % MOD;
			for (int k = i; k <= n; ++k)
				A[j][k] = (A[j][k] - A[i][k] * t) % MOD;
		}
	}
	if (ret < 0) ret += MOD;
	return ret;
}
void makeMatrix(Matrix& A, int n, int sweet1, int bad){
	int sweet0 = n - bad - sweet1, d1 = sweet1, d2 = d1 + sweet0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (i == j)
				A[i][i] = i <= d1 ? n - sweet0 - 1 : i <= d2 ? bad : n - 1;
			else
				A[i][j] = -!(i <= d2 && j <= d2 && !(i <= d1 && j <= d1));
	A.sz = n - 1;
}
void calcF(int n, int bad){
	static LL C[50][50];
	static Matrix A;
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= i; ++j)
			C[i][j] = j ? (C[i - 1][j] + C[i - 1][j - 1]) % MOD : 1;
	for (int i = 0; i <= n - bad; ++i){
		makeMatrix(A, n, i, bad);
		F[i] = det(A);
		for (int j = 0; j < i; ++j) F[i] = (F[i] - C[i][j] * F[j]) % MOD;
		if (F[i] < 0) F[i] += MOD;
	}
}
struct pack{
	int sum, num;
}A[1 << 20], B[1 << 20];
bool cmpLess(const pack& a, const pack& b){
	return a.sum < b.sum;
}
bool cmpGreater(const pack& a, const pack& b){
	return a.sum > b.sum;
}
int lg2[1 << 20];
int generateSubset(vector<int> A, pack* ret){
	ret[0] = pack{0, 0};
	int n = A.size(), len = 1 << n;
	for (int i = 0; i < n; ++i)
		lg2[1 << i] = i;
	for (int i = 1; i < len; ++i)
		ret[i] = pack{ret[i ^ (i & -i)].sum + A[lg2[i & -i]], __builtin_popcount(i)};
	return len;
}
class SweetFruits {
	public:
	int countTrees(vector <int> sweetness, int maxSweetness) {
		int n = sweetness.size();
		int cntbad = 0;
		vector<int> sweets;
		for (int i = 0; i < n; ++i)
			if (sweetness[i] == -1)
				++cntbad;
			else
				sweets.push_back(sweetness[i]);
		calcF(n, cntbad);
		int n2 = sweets.size();
		int len1 = generateSubset(vector<int>(sweets.begin(), sweets.begin() + n2 / 2), A);
		int len2 = generateSubset(vector<int>(sweets.begin() + n2 / 2, sweets.end()), B);
		sort(A, A + len1, cmpGreater); sort(B, B + len2, cmpLess);
		int cntn[40]; memset(cntn, 0, sizeof cntn);
		int pos = 0;
		LL ret = 0;
		for (int i = 0; i < len1; ++i){
			while (pos < len2 && B[pos].sum + A[i].sum <= maxSweetness) // 2 pointers (1?)
				cntn[B[pos++].num]++;
			for (int j = 0; j <= n2 / 2 + 1; ++j)
				ret = (ret + cntn[j] * F[j + A[i].num]) % MOD;
		}
		if (ret < 0) ret += MOD;
		return ret;
	}
};

/*
	'For the king for the land for the mountains
	For the green valleys where dragons fly
	For the glory the power to win the black lord
	I will search for the emerald sword'
		- Emerald Sword
*/

