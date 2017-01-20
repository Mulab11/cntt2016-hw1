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

const int maxn = 2e6+115;
const int mod = 1e9+7;

int jc[maxn];
int nc[maxn];
int Two[maxn];

LL Pow(LL x, int y)
{
	LL S = 1;
	while (y) {
		if (y & 1) S = S * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return S;
}

void Prepare()
{
	jc[0] = 1;
	for (int i = 1; i < maxn; ++i) {//预处理阶乘，阶乘逆元，2的幂
		jc[i] = (LL)jc[i - 1] * i % mod;
	}
	nc[maxn - 1] = Pow(jc[maxn - 1], mod - 2);
	for (int i = maxn - 2; i >= 0; --i) {
		nc[i] = (LL)nc[i + 1] * (i + 1) % mod;
	}
	Two[0] = 1;
	for (int i = 1; i < maxn; ++i) {
		Two[i] = (LL)Two[i - 1] * 2 % mod;
	}
}

int C(int x, int y)
{
	if (x < 0 || y < 0 || y > x) return 0;
	return (LL)jc[x] * nc[y] % mod * nc[x - y] % mod;
}

int Solve(int M, int R, int G, int B)
{
	int D = R - 1;
	int xg, xb, res;
	int Ans = 0;
	for (int xr = 0; xr <= D; ++xr) {//枚举G和B形成的长度为偶数的子段的个数
		if (((G - B) + (D - xr)) & 1) continue;
		xg = ((G - B) + (D - xr)) / 2;//G和B形成的长度为奇数且G多一个的子段的个数
		xb = ((D - xr) - (G - B)) / 2;//G和B形成的长度为奇数且G多一个的子段的个数
		if (xg < 0 || xb < 0) continue;
		res = G - xg - xr;
		if (res < 0) continue;
		(Ans += (LL)C(D, xr) * C(D - xr, xg) % mod * C(D + res - 1, D - 1) % mod * Two[xr] % mod) %= mod;//将这些子段插入在R之间
	}
	return Ans;
}

class LittleElephantAndBoard {
    public:
    int getNumber(int M, int R, int G, int B) {
		Prepare();
		R = M - R;
		G = M - G;
		B = M - B;
        return 2LL * ((LL)Solve(M, R, G, B) + Solve(M + 2, R + 2, G, B) + Solve(M + 1, R + 1, G, B) * 2LL) % mod;//讨论开头结束是否是R
    }
};
