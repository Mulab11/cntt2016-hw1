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

const int maxn = 1555;
const int maxc = 265;
const int mod = 1e9+9;

int n, L;
int color[maxn];
int jc[maxn], nv[maxn];
int Hsh[maxc][maxc], ht = 0;
int f[maxn][maxn];

int Gettip(char a, char b)
{
	if (Hsh[a][b] == 0) {
		Hsh[a][b] = ++ht;
	}
	return Hsh[a][b];
}

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

void Prepare()//预处理阶乘与逆元
{
	jc[0] = 1;
	for (int i = 1; i <= n; ++i) {
		jc[i] = (LL)jc[i - 1] * i % mod;
	}
	nv[n] = Pow(jc[n], mod - 2);
	for (int i = n - 1; i >= 0; --i) {
		nv[i] = (LL)nv[i + 1] * (i + 1) % mod;
	}
	reverse(color + 1, color + 1 + n);
}

int Solve()
{
	static int cs[maxn];
	int sum;
	memset(f, 0, sizeof(f));//f[i][j]表示当前已经能分辨出i座大楼，现在高度从大到小的前j座大楼已经安排好了且第j座大楼在最左边的方案数
	for (int i = 1; i <= L; ++i) {
		if (i != 1) {
			sum = 0;
			memset(cs, 0, sizeof(cs));
			for (int j = 1; j <= n; ++j) {//当上一座大楼与当前大楼颜色不同时，用前缀和优化
				if (j >= i) {
					f[i][j] = (LL)(sum - cs[color[j]] + mod) % mod * jc[j - 2] % mod;
				}
				(sum += (LL)f[i - 1][j] * nv[j - 1] % mod) %= mod;
				(cs[color[j]] += (LL)f[i - 1][j] * nv[j - 1] % mod) %= mod;
			}
		}
		else {
			f[i][1] = 1;//初始化
		}
		memset(cs, 0, sizeof(cs));
		for (int j = 1; j <= n; ++j) {//当上一座大楼颜色与当前大楼颜色相同时
			if (j >= i) {
				(f[i][j] += (LL)cs[color[j]] * jc[j - 2] % mod) %= mod;
			}
			(cs[color[j]] += (LL)f[i][j] * nv[j - 1] % mod) %= mod;
		}
	}
	int Ans = 0;
	for (int i = 1; i <= n; ++i) {//统计答案
		(Ans += (LL)f[L][i] * jc[n - 1] % mod * nv[i - 1] % mod) %= mod;
	}
	return Ans;
}

class ColorfulBuilding {
    public:
    int count(vector<string> color1, vector<string> color2, int _L) {
		ht = 0;
		n = 0;
		L = _L;
		memset(Hsh, 0, sizeof(Hsh));
		for (int i = 0; i < (int)color1.size(); ++i) {//将表示颜色的字符串hash为数字
			for (int j = 0; j < (int)color1[i].length(); ++j) {
				color[++n] = Gettip(color1[i][j], color2[i][j]);
			}
		}
		Prepare();//预处理阶乘以及阶乘的逆元
		return Solve();//Dp
    }
};

