#line 2 "MegaFactorial.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

int n, k;
int MOD;

int sz;// 矩阵的大小
int A[30][20][20];
int B[30][20][20];
int C[30][20][20];

int pw[30];
int ans[20][20];

// 快速幂
int fpm(int a, int b) {
	int ret = 1;
	while(b) {
		if(b & 1) ret = (ll)ret * a % MOD;
		a = (ll)a * a % MOD, b >>= 1;
	}
	return ret;
}

// 矩阵乘法
void mult(int A[20][20], int B[20][20]) {
	static int C[20][20];
	memset(C, 0, sizeof C);
	for(int k = 0; k <= sz; ++k)
		for(int i = 0; i <= sz; ++i)
			for(int j = 0; j <= sz; ++j)
				(C[i][j] += (ll)A[i][k] * B[k][j] % MOD) %= MOD;
	memcpy(A, C, sizeof C);
}

// 求出n，k时，质因子为p的和
int calc(int n, int k, int p) {
	memset(A, 0, sizeof A);
	int q = 0;ll t = 1;
	while(t <= n) q++, t *= p;
	q--, sz = k + 1;
	// 设T[i]表示i中含p的次数，第i个转移矩阵为G[i]
	// 那么G[i] = A[T[i]], T[i] <= log(n)
	for(int i = 0; i <= q; ++i) {
		for(int j = 1; j <= k; ++j)
			for(int r = j; r <= k; ++r)
				A[i][j][r]++;
		A[i][k + 1][k + 1] = 1;
		for(int j = 0; j <= k; ++j)
			A[i][k + 1][j] = i;
	}
	// B[i] = G[1] * G[2] * ... * G[p ^ i - 1]
	//      = (B[i - 1] * A[i - 1]) ^ (p - 1) * B[i - 1]
	for(int i = 0; i <= sz; ++i) B[0][i][i] = 1;
	for(int i = 1; i <= q; ++i) {
		memcpy(B[i], B[i - 1], sizeof B[i]);
		for(int j = 1; j < p; ++j) {
			mult(B[i], A[i - 1]);
			mult(B[i], B[i - 1]);
		}
	}
	// C[i] = G[1] * G[2] * ... * G[p ^ i]
	//      = B[i] * A[i]
	for(int i = 0; i <= q; ++i) {
		memcpy(C[i], B[i], sizeof B[i]);
		mult(C[i], A[i]);
	}
	// 接下来把n在p进制下分解就行，对应位为x就乘上对应的C ^ x即可
	pw[0] = 1;
	for(int i = 1; i <= q; ++i) pw[i] = pw[i - 1] * p;
	memset(ans, 0, sizeof ans);
	for(int i = 0; i <= sz; ++i) ans[i][i] = 1;
	while(n) {
		int x = n / pw[q], y = n % pw[q];
		for(int i = 1; i <= x; ++i) mult(ans, C[q]);
		n = y, q--;
	}
	return ans[k + 1][k];
}

class MegaFactorial {  
public:  
	int countTrailingZeros(int N, int K, int B) {
		n = N, k = K;

		// p[i], ind[i]分别为i的最大质因子和次数
		int p[] = {0, 0, 2, 3, 2, 5, 3, 7, 2, 3, 5};
		int ind[] = {0, 0, 1, 1, 2, 1, 1, 1, 3, 2, 1};

		// 为了整除ind[i]，我们要先把答案mod ind[i]的值求出来，然后把答案mod 10^9+9的值-这个值再去除以ind[i]
		MOD = ind[B];
		int ans = calc(n, k, p[B]);

		MOD = 1e9 + 9;
		ans = (ll)(calc(n, k, p[B]) - ans + MOD) * fpm(ind[B], MOD - 2) % MOD;
		
		return ans;
	}    
};  
