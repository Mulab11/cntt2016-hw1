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

const int mod = 1e9+7;
const int maxn = 1e5+115;

int n, m;
int jc[maxn], nc[maxn];//阶乘一节阶乘的逆元
int A[maxn], C[maxn];//组合数

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

int Comb(int x, int y)//求组合数
{
	if (x < 0 || y < 0 || x < y) return 0;
	return (LL)jc[x] * nc[y] % mod * nc[x - y] % mod;
}

void Prepare()//预处理阶乘
{
	const int N = 1e5;
	jc[0] = 1;
	for (int i = 1; i <= N; ++i) {
		jc[i] = 1LL * jc[i - 1] * i % mod;
	}
	nc[N] = Pow(jc[N], mod - 2);
	for (int i = N - 1; i >= 0; --i) {
		nc[i] = 1LL * nc[i + 1] * (i + 1) % mod;
	}
	for (int i = 0; i <= m; ++i) {
		C[i] = Comb(m, i);
	}
}

int Solve()//对于某一维求出答案
{
	int L, R;
	int Ans = 0, S;
	sort(A + 1, A + 1 + n);
	L = A[n] - m;
	R = A[1] + m;
	for (int i = L; i <= R; ++i) {
		S = 1;
		for (int j = 1; j <= n; ++j) {
			if ((m - abs(A[j] - i)) % 2 == 0) {
				S = (LL)S * C[(m - abs(A[j] - i)) / 2] % mod;
			}
			else {
				S = 0;
				break;
			}
		}
		(Ans += S) %= mod;
	}
	return Ans;
}

class WolfPack {
    public:
    int calc(vector<int> x, vector<int> y, int _m) {
		int ans1, ans2;
		n = x.size();
		m = _m;
		Prepare();
		for (int i = 1; i <= n; ++i) {//将这个坐标系旋转45度，就可以分为两维分别求解
			A[i] = y[i - 1] - x[i - 1];
		}
		ans1 = Solve();
		for (int i = 1; i <= n; ++i) {
			A[i] = x[i - 1] + y[i - 1];
		}
		ans2 = Solve();
        return (LL)ans1 * ans2 % mod;//最后相乘
    }
};
