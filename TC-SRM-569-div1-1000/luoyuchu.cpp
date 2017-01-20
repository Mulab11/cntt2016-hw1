#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>
void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

const int maxn = 19;
const int prime[4] = {7, 5, 3, 2};

int n;
int mod, mt;
struct Matrix
{
	int t[maxn][maxn];
	void reset()
	{
		memset(t, 0, sizeof(t));
	}
}I, One;

LL Pow(LL x, int y)//快速幂
{
	LL S = 1;
	while (y) {
		if (y & 1) S = S * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return S;
}

Matrix Mult(const Matrix &a, const Matrix &b)//矩阵乘法
{
	static Matrix c;
	c.reset();
	for (int i = 1; i <= mt; ++i) {
		for (int j = 1; j <= mt; ++j) {
			for (int k = 1; k <= mt; ++k) {
				(c.t[i][j] += (LL)a.t[i][k] * b.t[k][j] % mod) %= mod;
			}
		}
	}
	return c;
}

void Prepare(int K)//求出转移一步的转移矩阵
{
	mt = K + 1;
	I.reset();
	for (int i = 1; i <= mt; ++i) I.t[i][i] = 1;
	One.reset();
	for (int i = 1; i < mt; ++i) {
		for (int j = 1; j <= i; ++j) {
			One.t[j][i] = 1;
		}
	}
	One.t[mt][mt] = 1;
}

Matrix Fpm(Matrix x, int y)//矩阵快速幂
{
	Matrix S = I;
	while (y) {
		if (y & 1) S = Mult(S, x);
		x = Mult(x, x);
		y >>= 1;
	}
	return S;
}

int Solve(int p)
{
	int Ans = 0;
	int adv, times;
	Matrix S = I, Trans = One, Cz;
	for (int step = p; ; step *= p) {//step为质数p的幂，来统计这一质数出现的次数
		adv = n / step * step;
		if (adv == 0) break;//一次都没有出现
		Trans.t[mt - 1][mt] = 0;
		Trans = Fpm(Trans, p);//将转移矩阵也要p次方
		Trans.t[mt - 1][mt] = 1;		
		S = I;
		S = Mult(S, Fpm(One, n - adv));//之前的不够一次转移的部分
		times = adv / step;//可以转移几次
		Cz = Mult(S, Fpm(Trans, times));//总的转移矩阵
		for (int i = 1; i < mt; ++i) {//统计答案
			Ans = (Ans + Cz.t[i][mt]) % mod;
		}
	}
	return Ans;
}

class MegaFactorial {
    public:
    int countTrailingZeros(int _N, int _K, int B) {
		int cnt = 0, bp;
		int res, ans;
		n = _N;
		Prepare(_K);
		for (int i = 0; i < 4; ++i) {//求出B中最大的质数，和它出现的次数
			if (B % prime[i] == 0) {
				while (B % prime[i] == 0) {
					B /= prime[i];
					++cnt;
				}
				bp = prime[i];
				break;
			}
		}
		mod = cnt;//先求出对于幂次取模的余数
		res = Solve(bp);
		mod = 1e9+9;
		ans = Solve(bp);
		return (ans - res + mod) % mod * Pow(cnt, mod - 2) % mod;//之后可以直接将答案减去余数乘上逆元即可
    }
};
