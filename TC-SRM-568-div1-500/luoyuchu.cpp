#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define fi first
#define se second
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

const int maxn = 105;
const int mod = 1e9+7;

int n;
int mat[maxn][maxn];//原矩阵
int fa[maxn];//每个点所属联通块
pair<int, int> val[maxn];//val[i].first表示他的一次项的系数，second表示常数项
bool vis[maxn];//是否访问过
bool FAIL;//发生冲突
int bounder[maxn][2], bt = 0;//每个联通块的左右边界

pair<int, int> operator - (const pair<int, int> &a, const pair<int, int> &b)
{
	return mp(a.fi - b.fi, a.se - b.se);
}
pair<int, int> operator + (const pair<int, int> &a, const pair<int, int> &b)
{
	return mp(a.fi + b.fi, a.se + b.se);
}
bool operator == (const pair<int, int> &a, const pair<int, int> &b)
{
	return (a.fi == b.fi && a.se == b.se);
}

void Dfs(int p, int f)//搜索联通块
{
	vis[p] = 1;
	fa[p] = f;
	if (p <= n) {
		for (int i = 1; i <= n; ++i) {
			if (mat[p][i] != -1)  {
				if (vis[i + n] == 0) {//未访问
					val[i + n] = mp(0, mat[p][i]) - val[p];
					Dfs(i + n, f);
				}
				else {//如果已经访问，则检查合法性
					if (!((val[i + n] + val[p]) == mp(0, mat[p][i]))) {
						FAIL = 1;
						return;
					}
				}
			}
		}
	}
	else {
		p -= n;
		for (int i = 1; i <= n; ++i) {
			if (mat[i][p] != -1) {
				if (vis[i] == 0) {//未访问
					val[i] = mp(0, mat[i][p]) - val[p + n];
					Dfs(i, f);
				}
				else {//如果已经访问，则检查合法性
					if (!((val[i] + val[p + n]) == mp(0, mat[i][p]))) {
						FAIL = 1;
						return;
					}
				}
			}
		}
	}
}

int Stat()
{
	LL Ans = 1;
	LL Nans = 1;
	for (int i = 1; i <= bt; ++i) {//统计总方案数，由于可以让所有联通块同时减去1,还用统计所有联通块均不取到下界的情况，用总方案减去之
		Ans = (Ans * (bounder[i][1] - bounder[i][0] + 1)) % mod;
		Nans = (Nans * (bounder[i][1] - bounder[i][0])) % mod;
	}
	return (Ans - Nans + mod) % mod;
}

int Solve()
{
	int l, r;
	bt = 0;
	FAIL = 0;
	memset(fa, 0, sizeof(fa));
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1; i <= n; ++i) {
		if (vis[i] == 0) {//一个一个找出联通块
			val[i] = mp(1, 0);
			fa[i] = i;
			Dfs(i, i);
			if (FAIL) {
				return 0;
			}
			l = 0, r = 9;//对于联通块的每个元素，更新上下界
			for (int j = 1; j <= n; ++j) {
				if (fa[j] == i) {
					Ckmax(l, -val[j].se);
				}
			}
			for (int j = 1; j <= n; ++j) {
				if (fa[j + n] == i) {
					Ckmin(r, val[j + n].se);
				}
			}
			if (l > r) {
				return 0;
			}
			++bt;
			bounder[bt][0] = l;
			bounder[bt][1] = r;
		}
	}
	return Stat();//统计方案数
}

class EqualSums {
    public:
    int count(vector<string> board) {
		n = board.size();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (board[i][j] == '-') mat[i + 1][j + 1] = -1;
				else mat[i + 1][j + 1] = board[i][j] - '0';
			}
		}
		return Solve();//开始计算
    }
};
