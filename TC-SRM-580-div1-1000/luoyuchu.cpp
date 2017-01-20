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

int n, m;
int mat[maxn][maxn];
int f[maxn][maxn];
int g[maxn][maxn][2];
int ps[maxn];

int Solve()
{
	int Min = 2e9, Max;
	for (int i = 1; i <= m; ++i) {
		f[n][i] = mat[n][i];//f[i][j]表示从(i,j)的格子开始走的最优代价
	}
	for (int i = n - 1; i >= 1; --i) {//我们发现，如果当前的格子底部没有隔板，那么一定要向下走，否则可以被限制到最后还是回到这个格子
		memset(g, 0x3f, sizeof(g));//g[i][j][0/1]表示这一行[l,r]的格子底部已经放置了隔板，现在在l/r，之后要完成游戏的最优代价
		memset(ps, 0, sizeof(ps));
		for (int j = 1; j <= m; ++j) ps[j] = ps[j - 1] + mat[i][j];
		g[2][m][0] = f[i + 1][1] + mat[i][1];
		g[2][m][1] = f[i + 1][1] + ps[m - 1];
		g[1][m - 1][0] = f[i + 1][m] + ps[m] - ps[1];
		g[1][m - 1][1] = f[i + 1][m] + mat[i][m];
		for (int L = m - 2; L >= 1; --L) {
			for (int a = 1; a + L - 1 <= m; ++a) {//考虑一种状态，枚举下一步是从左还是从右边走
				int b = a + L - 1;
				//------------------------on the left boundary
				Min = 2e9;
				if (a != 1) {
					Max = 0;
					Ckmax(Max, mat[i][a - 1] + f[i + 1][a - 1]);
					Ckmax(Max, mat[i][a - 1] + g[a - 1][b][0]);
					Ckmin(Min, Max);
				}
				if (b != m) {
					Max = 0;
					Ckmax(Max, ps[b + 1] - ps[a] + f[i + 1][b + 1]);
					Ckmax(Max, ps[b + 1] - ps[a] + g[a][b + 1][1]);
					Ckmin(Min, Max);
				}
				g[a][b][0] = Min;
				//------------------------on the right boundary
				Min = 2e9;
				if (a != 1) {
					Max = 0;
					Ckmax(Max, ps[b - 1] - ps[a - 2] + f[i + 1][a - 1]);
					Ckmax(Max, ps[b - 1] - ps[a - 2] + g[a - 1][b][0]);
					Ckmin(Min, Max);
				}
				if (b != m) {
					Max = 0;
					Ckmax(Max, mat[i][b + 1] + f[i + 1][b + 1]);
					Ckmax(Max, mat[i][b + 1] + g[a][b + 1][1]);
					Ckmin(Min, Max);
				}
				g[a][b][1] = Min;
			}
		}
		for (int j = 1; j <= m; ++j) {//更新f数组
			f[i][j] = max(g[j][j][0], f[i + 1][j]) + mat[i][j];
		}
	}
	Min = 2e9;
	for (int i = 1; i <= m; ++i) {
		Ckmin(Min, f[1][i]);
	}
	return Min;//返回答案
}

class WallGameDiv1 {
    public:
    int play(vector<string> costs) {
		n = costs.size();
		m = costs[0].length();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				mat[i + 1][j + 1] = costs[i][j] - '0';
			}
		}
		if (m == 1) {//特殊判断m=1的情况
			int sum = 0;
			for (int i = 1; i <= n; ++i) {
				sum += mat[i][1];
			}
			return sum;
		}
		return Solve();//解决问题
    }
};

