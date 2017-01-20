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

const int maxk = 333;
const int maxn = 533;
const int maxm = 2555;
const int walk[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int n, m, K;
long double Ans = 0;
long double C[maxn][maxn];//组合数 
char fd[maxn][maxn];//输入矩阵
int mat[maxn][maxn], Index;//dfn序
struct edge//树边
{
	int to, next;
	edge() {}
	edge(int _t, int _n):to(_t), next(_n) {}
}e[maxm * 2];
int head[maxm], et = -1;
int lst[maxk], lt = 0;//checkpoint列表
int pa[15][maxm], deep[maxm];//2^i的祖先，深度

void Prepare()//求组合数
{
	for (int i = 0; i < maxn; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
}

void Addedge(int x, int y)//加边
{
	e[++et] = edge(y, head[x]), head[x] = et;
	e[++et] = edge(x, head[y]), head[y] = et;
}

void Dfs1(int x, int y)//求dfs序，并将树建出
{
	int tx, ty;
	mat[x][y] = ++Index;
	if (fd[x][y] == '*') lst[++lt] = Index;
	for (int i = 0; i < 4; ++i) {
		tx = x + walk[i][0];
		ty = y + walk[i][1];
		if (tx > 0 && tx <= n && ty > 0 && ty <= m && fd[tx][ty] != '#') {
			if (mat[tx][ty] == 0) Dfs1(tx, ty);
			if (mat[tx][ty] > mat[x][y]) Addedge(mat[x][y], mat[tx][ty]);
		}
	}
}

void Dfs2(int p)//求出每个点的父亲
{
	for (int i = head[p]; i != -1; i = e[i].next) {
		if (pa[0][p] != e[i].to) {
			pa[0][e[i].to] = p;
			deep[e[i].to] = deep[p] + 1;
			Dfs2(e[i].to);
		}
	}
}

void Build(vector<string> field, int _k)
{
	n = field.size();
	m = field[0].length();
	K = _k;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			fd[i + 1][j + 1] = field[i][j];
		}
	}
	memset(head, -1, sizeof(head));
	et = -1;
	memset(mat, 0, sizeof(mat));
	Index = 0;
	lt = 0;
	for (int i = 1; i <= n; ++i) {//从一个点开始遍历出树
		for (int j = 1; j <= m; ++j) {
			if (fd[i][j] != '#') {
				Dfs1(i, j);
				goto Break;
			}
		}
	}
	Break:;
	memset(pa[0], 0, sizeof(pa[0]));
	deep[1] = 1;
	Dfs2(1);
	for (int i = 1; i <= 13; ++i) {//预处理每个点的第2^i代祖先
		for (int j = 1; j <= Index; ++j) {
			pa[i][j] = pa[i - 1][pa[i - 1][j]];
		}
	}
}

int Lca(int x, int y)//求最近公共祖先
{
	if (x == y) return x;
	if (deep[x] < deep[y]) swap(x, y);
	for (int i = 13; i >= 0; --i) {
		if (deep[pa[i][x]] >= deep[y]) {
			x = pa[i][x];
		}
	}
	if (x == y) return x;
	for (int i = 13; i >= 0; --i) {
		if (pa[i][x] != pa[i][y]) {
			x = pa[i][x];
			y = pa[i][y];
		}
	}
	return pa[0][x];
}

void Calc_full()//计算如果从根出发到根结束，路径长度的期望
{
	for (int i = 1; i <= lt; ++i) {
		for (int j = i + 1; j <= lt; ++j) {
			Ans += C[lt - (j - i + 1)][K - 2] * (deep[lst[i]] + deep[lst[j]] - deep[Lca(lst[i], lst[j])] * 2);
		}
	}
	for (int i = 1; i <= lt; ++i) {
		Ans += (deep[lst[i]] - 1) * C[lt - i][K - 1];
		Ans += (deep[lst[i]] - 1) * C[i - 1][K - 1];
	}
}

void Calc_common()//所有点的lca到根的路径长度的两倍是多算的，要减去
{
	for (int i = 1; i <= lt; ++i) {
		for (int j = i + 1; j <= lt; ++j) {
			Ans -= C[j - i - 1][K - 2] * (deep[Lca(lst[i], lst[j])] - 1) * 2;
		}
	}
}

void Calc_lca()//由于可以任意点出发与结束，所以所选的点构成的虚树的直径也要减去
{
	int cnt;
	static int dist[maxk][maxk];
	for (int i = 1; i <= lt; ++i) {
		for (int j = i + 1; j <= lt; ++j) {
			dist[i][j] = dist[j][i] = deep[lst[i]] + deep[lst[j]] - deep[Lca(lst[i], lst[j])] * 2;
		}
	}
	for (int i = 1; i <= lt; ++i) {
		for (int j = i + 1; j <= lt; ++j) {
			cnt = 0;
			for (int k = 1; k <= lt; ++k) {
				if (k != i && k != j && (dist[i][k] < dist[i][j] || (dist[i][k] == dist[i][j] && k > j)) && (dist[k][j] < dist[i][j] || (dist[k][j] == dist[i][j] && k > i))) {
					++cnt;
				}
			}
			Ans -= dist[i][j] * C[cnt][K - 2];
		}
	}
}

void Solve()
{
	Ans = 0;
	if (K == 1 || K == 0) return;
	Calc_full();//计算如果从根出发到根结束，路径长度的期望
	Calc_common();//所有点的lca到根的路径长度的两倍是多算的，要减去
	Calc_lca();//由于可以任意点出发与结束，所以所选的点构成的虚树的直径也要减去
	Ans /= C[lt][K];//之前计算并未除分母
}

class Orienteering {
    public:
    double expectedLength(vector<string> field, int _k) {
		Prepare();
		Build(field, _k);
		Solve();
        return Ans;
    }
};

