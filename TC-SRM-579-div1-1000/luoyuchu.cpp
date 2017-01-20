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

const int maxn = 55;

int n;
int P[maxn][3];
double jc[maxn], mi[maxn];
double f[maxn][maxn][maxn];//f[a][b][c]表示局面出现对手已经随机出了a个石头，b张纸，c把剪刀的概率
double conseq[maxn][maxn][maxn][3];//conseq[a][b][c][0-2]表示当对手已经出了a个石头，b张纸，c把剪刀的下一步出石头/纸/剪刀的概率

double Solve()
{
	double Ans = 0;
	f[0][0][0] = 1;
	for (int i = 0; i < n; ++i) {//首先如果将概率转化为求方案数，求出不带阶乘的f
		for (int s = i; s >= 0; --s) {
			for (int a = 0; a <= s; ++a) {
				for (int b = 0; a + b <= s; ++b) {
					int c = s - a - b;
					f[a + 1][b][c] += f[a][b][c] * P[i + 1][0];
					f[a][b + 1][c] += f[a][b][c] * P[i + 1][1];
					f[a][b][c + 1] += f[a][b][c] * P[i + 1][2];
				}
			}
		}
	}
	jc[0] = 1;
	for (int i = 1; i <= n; ++i) {
		jc[i] = jc[i - 1] * i;
	}
	mi[0] = 1;
	for (int i = 1; i <= n; ++i) {
		mi[i] = mi[i - 1] * 300;
	}
	for (int a = 0; a < n; ++a) {
		for (int b = 0; a + b < n; ++b) {
			for (int c = 0; a + b + c < n; ++c) {//conseq[a][b][c]极为对应的两个f[][][]稍作变化的商
				conseq[a][b][c][0] = f[a + 1][b][c] * (a + 1) * jc[(a + b + c)] * jc[n - a - b - c - 1] / jc[n] / mi[a + b + c + 1];
				conseq[a][b][c][1] = f[a][b + 1][c] * (b + 1) * jc[(a + b + c)] * jc[n - a - b - c - 1] / jc[n] / mi[a + b + c + 1];
				conseq[a][b][c][2] = f[a][b][c + 1] * (c + 1) * jc[(a + b + c)] * jc[n - a - b - c - 1] / jc[n] / mi[a + b + c + 1];
			}
		}
	}
	for (int a = 0; a <= n; ++a) {
		for (int b = 0; a + b <= n; ++b) {
			for (int c = 0; a + b + c <= n; ++c) {//转化为概率
				f[a][b][c] = f[a][b][c] * jc[a + b + c] * jc[n - a - b - c] / jc[n] / mi[a + b + c];
			}
		}
	}
	for (int a = 0; a < n; ++a) {
		for (int b = 0; a + b < n; ++b) {
			for (int c = 0; a + b + c < n; ++c) {
				for (int i = 0; i < 3; ++i) {//conseq[a][b][c]极为对应的两个f[][][]的商
					conseq[a][b][c][i] /= f[a][b][c];
				}
			}
		}
	}
	for (int a = 0; a < n; ++a) {
		for (int b = 0; a + b < n; ++b) {
			for (int c = 0; a + b + c < n; ++c) {//最后对于每一种局面，我们选择一个最优的策略
				double Max = 0;
				for (int i = 0; i < 3; ++i) {
					Ckmax(Max, f[a][b][c] * (conseq[a][b][c][i] + conseq[a][b][c][(i + 2) % 3] * 3));
				}
				Ans += Max;
			}
		}
	}
	return Ans;
}

class RockPaperScissors {
    public:
    double bestScore(vector<int> rockProb, vector<int> paperProb, vector<int> scissorsProb) {
		n = rockProb.size();
		memset(f, 0, sizeof(f));
		memset(conseq, 0, sizeof(conseq));
		for (int i = 0; i < n; ++i) {
			P[i + 1][0] = rockProb[i];
			P[i + 1][1] = paperProb[i];
			P[i + 1][2] = scissorsProb[i];
		}
		return Solve();
    }
};

