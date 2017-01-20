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

const int maxn = 1755;
const int mod = 555555555;

int H, W;
int Rc, Cc, S;
int C[maxn][maxn];
int g[maxn][maxn];
LL Ans;

void Prepare()//预处理C[][]组合数，以及g[i][j]将i个无编号的物品放入j个箱子中，箱子可以为空，也可以放任意多个的方案数
{
	for (int i = 0; i < maxn; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}
	memset(g, 0, sizeof(g));
	g[0][0] = 1;
	for (int i = 0; i < maxn; ++i) {
		for (int j = 1; j < maxn; ++j) {
			if (i > 0) g[i][j] += g[i - 1][j];
			if (j > 0) g[i][j] += g[i][j - 1];
			g[i][j] %= mod;
		}
	}
}

void Solve()
{
	int l, r, mid;
	int det;
	for (int i = 0; i <= min(Rc, H); ++i) {//首先枚举有多少行被翻了奇数次
		if ((Rc - i) % 2) continue;
		det = (H - i) - i;//此时每翻一列使得1的个数的变化量
		if (det == 0) {//如果为0，则列怎么翻都可以
			if (i * W == S) {
				Ans = (Ans + (LL)C[H][i] * g[(Rc - i) / 2][H] % mod * g[Cc][W] % mod) % mod;
			}
		}
		else if (det > 0) {//每翻一列，个数增加
			l = 0, r = min(Cc, W);
			while (l != r) {//二分列数
				mid = (l + r) / 2;
				if (i * W + mid * H - mid * i * 2 < S) l = mid + 1;
				else r = mid;
			}
			if (i * W + l * H - i * l * 2 != S) continue;
			if ((Cc - l) % 2) continue;
			Ans = (Ans + (LL)C[H][i] * C[W][l] % mod * g[(Rc - i) / 2][H] % mod * g[(Cc - l) / 2][W] % mod) % mod;//统计此情况下的方案数
		}
		else {//每翻一列，个数减少
			l = 0, r = min(Cc, W);
			while (l != r) {//二分列数
				mid = (l + r) / 2;
				if (i * W + mid * H - mid * i * 2 > S) l = mid + 1;
				else r = mid;
			}
			if (i * W + l * H - i * l * 2 != S) continue;
			if ((Cc - l) % 2) continue;
			Ans = (Ans + (LL)C[H][i] * C[W][l] % mod * g[(Rc - i) / 2][H] % mod * g[(Cc - l) / 2][W] % mod) % mod;//统计此情况下的方案数
		}
	}
}

class XorBoard {
    public:
    int count(int _H, int _W, int Rcount, int Ccount, int _S) {
		H = _H;
		W = _W;
		Rc = Rcount;
		Cc = Ccount;
		S = _S;
		Ans = 0;
		Prepare();//预处理
		Solve();//枚举
        return Ans;//返回答案
    }
};


