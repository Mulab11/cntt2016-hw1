#include <bits/stdc++.h>
using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)

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

using namespace std;

const int maxn = 2505;

int n;
int A[maxn];
long double P[2];
struct Matrix
{
	long double t[2][2];
	void reset()
	{
		memset(t, 0, sizeof(t));
	}
}Trans;

Matrix Mult(const Matrix &a, const Matrix &b)//矩阵乘法
{
	static Matrix c;
	c.reset();
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			for (int k = 0; k < 2; ++k) {
				c.t[i][j] += a.t[i][k] * b.t[k][j];
			}
		}
	}
	return c;
}

Matrix Fpm(Matrix x, int y)//矩阵快速幂
{
	Matrix S;
	S.reset();
	S.t[0][0] = S.t[1][1] = 1;
	while (y) {
		if (y & 1) S = Mult(S, x);
		x = Mult(x, x);
		y >>= 1;
	}
	return S;
}

void Prepare(int K)
{
	int N = n * (n - 1) / 2;
	Matrix S;
	Trans.reset();
	Trans.t[0][0] = (N - (n - 1)) * (long double)1.0 / N;//转移矩阵
	Trans.t[0][1] = (long double)1.0 / N;
	Trans.t[1][0] = (n - 1) * (long double)1.0 / N;
	Trans.t[1][1] = (N - (n - 1)) * (long double)1.0 / N + (n - 2) * (long double)1.0 / N;
	S = Fpm(Trans, K);
	P[0] = S.t[0][0] * 1;//位于原来的位置的概率
	P[1] = S.t[0][1] * 1;//位于其他位置的概率
}

double Solve()
{
	long double S = 0;
	int N = 0;
	for (int i = n; i >= 1; --i) {
		N += i * (n - i + 1);
	}
	for (int i = 1; i <= n; ++i) {
		S += ((N - (n - i + 1) * i) * P[1] + (n - i + 1) * i * P[0]) * A[i];//对于每个位置的数字，算出他对总期望的贡献
	}
	S /= (n + 1) * n / 2;
	return S;
}

class TheSwapsDivOne {
    public:
    double find(vector<string> seq, int k) {
		n = 0;
		for (int i = 0; i < seq.size(); ++i) {
			for (int j = 0; j < seq[i].length(); ++j) {
				A[++n] = seq[i][j] - '0';
			}
		}
		Prepare(k);//求出K次操作之后处于不同位置的概率
		return Solve();//计算期望
    }
};

