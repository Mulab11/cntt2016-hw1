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

const int maxn = 55;

int n;
int L[maxn], D[maxn];
int f[maxn][maxn], g[maxn][maxn];

int Dp()//Dp，f[i][j]表示这一个环上从i顺时针到j这一段被消除的最大收益
{
	memset(f, 0, sizeof(f));
	for (int i = 0; i < n; ++i) {
		if (L[i] == 1) {
			f[i][i] = D[i];
		}
	}
	for (int Len = 2; Len <= n; ++Len) {
		for (int st = 0; st < n; ++st) {
			int end = (st + Len) % n;
			memset(g, -0x3f, sizeof(g));
			g[0][st] = 0;//g[i][j]表示从st开始到了j,已经选取i个用于st这个点的L来消除
			for (int i = 0; i <= L[st] - 1; ++i) {//我们从起点st开始需要找到L[st]个消除，其他的可以使用f[l][r]更新
				for (int j = st; (j + 1) % n != end; j = (j + 1) % n) {
					if (g[i][j] >= 0) {
						Ckmax(g[i + 1][(j + 1) % n], g[i][j]);
						for (int k = (j + 1) % n; ; ) {
							Ckmax(g[i][k], g[i][j] + f[(j + 1) % n][k]);
							k = (k + 1) % n;
							if (k == end) break;
						}
					}
				}
			}
			if (g[L[st] - 1][(st + Len - 1) % n] >= 0) {
				f[st][(st + Len - 1) % n] = g[L[st] - 1][(st + Len - 1) % n] + D[st];//如果有合法解，需要加上消除st的收益
			}
		}
	}
	int Ans = 0;
	for (int i = 0; i < n; ++i) {
		Ckmax(Ans, f[i][(i + n - 1) % n]);
	}
	return Ans;
}

class SpellCards {
    public:
    int maxDamage(vector<int> level, vector<int> damage) {
		n = level.size();
		for (int i = 0; i < n; ++i) {
			L[i] = level[i];
			D[i] = damage[i];
		}
		return Dp();
    }
};

