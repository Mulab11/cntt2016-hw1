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
const int mod = 1e9+7;

int n, m, Ans;
char mat[maxn][maxn];//原图
bool pre[maxn][maxn], suf[maxn][maxn];//pre[i][j]表示第i行的前缀j是否合法,suf同理
int f[maxn][maxn];

void Prepare(char L, char R)//求前缀后缀
{
	memset(pre, 0, sizeof(pre));
	memset(suf, 0, sizeof(suf));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			pre[i][j] = pre[i][j - 1] | (mat[i][j] == R);
		}
		for (int j = m; j >= 1; --j) {
			suf[i][j] = suf[i][j + 1] | (mat[i][j] == L);
		}
	}
}

void Dp()//Dp，f[i][j]表示考虑前i行，第i行前j个格子是一种颜色，后面起他是一种颜色
{
	static int sum[maxn];
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		memset(sum, 0, sizeof(sum));
		sum[0] = f[i - 1][0];
		for (int j = 1; j <= m; ++j) sum[j] = (sum[j - 1] + f[i - 1][j]) % mod;
		for (int j = 0; j <= m; ++j) {
			if (pre[i][j] == 0 && suf[i][j + 1] == 0) {
				f[i][j] = sum[j];
			}
		}
	}
	for (int i = 0; i <= m; ++i) {
		Ans = ((LL)Ans + f[n][i]) % mod;
	}
}

void Sub()//减去由于分割线为一条直线而多算的情况
{
	bool ok;
	bool pp[maxn], ss[maxn];
	memset(pp, 0, sizeof(pp));
	memset(ss, 0, sizeof(ss));
	for (int i = 1; i <= n; ++i) pp[i] = pp[i - 1] | pre[i][m];
	for (int i = n; i >= 1; --i) ss[i] = ss[i + 1] | suf[i][1];
	for (int i = 1; i < n; ++i) {
		if (pp[i] == 0 && ss[i + 1] == 0) {
			--Ans;
		}
	}
	for (int i = 0; i <= m; ++i) {
		ok = 1;
		for (int j = 1; j <= n; ++j) {
			if (pre[j][i] || suf[j][i + 1]) {
				ok = 0;
				break;
			}
		}
		if (ok) Ans = (Ans - 1 + mod) % mod;
	}
}

void Solve(bool flag)//调用函数
{
	Prepare('W', 'B');
	Dp();
	if (flag) Sub();
	Prepare('B', 'W');
	Dp();
	if (flag) Sub();
}

void Trans()//将每一行去反，可以用同一个函数解决另一种情况
{
	for (int i = 1; i <= n; ++i) {
		reverse(mat[i] + 1, mat[i] + 1 + m);
	}
}

void Whole()//将这个图都是一种颜色而多算的情况去重
{
	bool ok1, ok2;
	ok1 = 1;
	ok2 = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (mat[i][j] == 'W') ok1 = 0;
			if (mat[i][j] == 'B') ok2 = 0;
		}
	}
	Ans -= ok1 + ok2;
	Ans = (Ans + mod) % mod;
}

class TwoConvexShapes {
    public:
    int countWays(vector<string> grid) {
		n = grid.size();
		m = grid[0].length();
		Ans = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				mat[i][j] = grid[i - 1][j - 1];
			}
		}
		Solve(0);
		Trans();
		Solve(1);
		Whole();
        return Ans;
    }
};
