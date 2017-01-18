#line 2 "MegaFactorial.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 40
#define moo 1000000009
typedef long long ll;
using namespace std;
ll mo;
int n, k, b;
void add(ll &a, ll b) {
	a += b; a %= mo;
}
struct mat{ // 以下为矩阵运算部分
	ll x[maxn][maxn];
	ll * operator [] (const int &num) {
		return x[num];
	}
}A[maxn];　// A[i]表示由f[0][*]转移到f[p ^ i][*]所需要乘上的矩阵
mat operator * (const mat &a, const mat &b) {
	mat c; cl(c.x);
	for (int p = 0; p <= k; ++p)
		for (int i = 0; i <= k; ++i)
			for (int j = 0; j <= k; ++j)
				add(c[i][j], 1ll * a.x[i][p] * b.x[p][j] % mo);
	return c;
}
mat operator ^ (mat a, int b) {
	mat c; cl(c.x);
	for (int i = 0; i <= k; ++i) c[i][i] = 1;
	for (; b; b >>= 1, a = a * a)
		if (b & 1) c = c * a;
	return c;
}
ll calc(int n, int p, int c) {
	mo = 1ll * moo * c; // floor(ans / c) % moo = floor((ans % (c * moo)) / c)
	for (int q = 0; q <= 30; ++q) { // 先计算出从f[p ^ q - 1][*]转移到f[p ^ q][*]的矩阵
		cl(A[q].x);
		A[q][0][0] = 1; // 固定一个1，便于之后计算常数项
		for (int i = 1; i <= k; ++i) {
			A[q][0][i] = q; // 常数项f[p ^ q][0] = q
			for (int j = 1; j <= i; ++j)
				A[q][j][i] = 1; // f[p ^ q][i] = \sum_{j = 1}^{i} f[p ^ q - 1][j] + f[p ^ q][0]
		}
	}
	for (int q = 1; q <= 30; ++q) 
		for (int prev = 0; prev < q; ++prev) // A[q] = A[q - 1] ^ (p - 1) * A[q - 2] ^ (p - 1) ... A[0] ^ (p - 1) * A[q]
			A[q] = (A[prev] ^ (p - 1)) * A[q];
	int dig[maxn];
	cl(dig);
	for (int i = 0; i <= 30; ++i) {
		if (!n) break;
		dig[i] = n % p; n /= p; // 求出n的p进制表示
	}
	mat ans; cl(ans.x); for (int i = 0; i <= k; ++i) ans[i][i] = 1;
	for (int i = 30; i >= 0; --i)
		ans = ans * (A[i] ^ dig[i]); // 从f[0][*]转移到f[p ^ i][*], 与从f[x][*]转移到f[x + p ^ i][*],其中x里p的个数至少为i，所需要乘的矩阵是一样的
	return ans[0][k] / c;
}
class MegaFactorial {
	public:
		int countTrailingZeros(int N, int K, int B) {
			n = N; k = K; b = B;
			if (B == 2 || B == 3 || B == 5 || B == 7)
				return calc(N, B, 1);
			if (B == 4) return calc(N, 2, 2);
			if (B == 6) return min(calc(N, 2, 1), calc(N, 3, 1)) % moo;
			if (B == 8) return calc(N, 2, 3);
			if (B == 9) return calc(N, 3, 2);
			return min(calc(N, 2, 1), calc(N, 5, 1)) % moo;
		}
};
