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

const int maxn = 41;
const int mod = 1e9+9;
const int walk[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int n, m;
char mat[maxn][maxn];
int fa[maxn * maxn], rak[maxn * maxn], cnt[maxn * maxn];
int stat[maxn][maxn][maxn][maxn];

int Gettip(int x, int y)//二维标号转一维
{
	return (x - 1) * m + y;
}

bool In(int x, int y)//判断是否在棋盘内
{
	return (x >= 1 && x <= n && y >= 1 && y <= m);
}

void Init(vector<string> b)//输入
{
	n = b.size();
	m = b[0].length();
	memset(mat, 0, sizeof(mat));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			mat[i + 1][j + 1] = b[i][j];
		}
	}
}

const int maxl = maxn * maxn * maxn * maxn / 2 + 5;
int line[maxl - 5][4];
int lh, lt;

void Addline(int x1, int y1, int x2, int y2)//加入队列
{
	lh = (lh == maxl) ? 0 : (lh + 1);
	line[lh][0] = x1;
	line[lh][1] = y1;
	line[lh][2] = x2;
	line[lh][3] = y2;
	stat[x1][y1][x2][y2] = 1;
}

void Bfs()//Bfs搜索可行点对
{
	int h = 0, t = 0;
	static int tx1, tx2, ty1, ty2, x1, y1, x2, y2;
	while (lh != lt) {
		x1 = line[lt][0];
		y1 = line[lt][1];
		x2 = line[lt][2];
		y2 = line[lt][3];
		lt = (lt == maxl) ? 0 : (lt + 1);
		for (int i = 0; i < 4; ++i) {
			tx1 = x1 + walk[i][0];
			ty1 = y1 + walk[i][1];
			tx2 = x2 + walk[i][0];
			ty2 = y2 + walk[i][1];//两边都移动
			if (In(tx1, ty1) && In(tx2, ty2) && mat[tx1][ty1] != '#' && mat[tx2][ty2] != '#' && stat[tx1][ty1][tx2][ty2] == -1) {
				Addline(tx1, ty1, tx2, ty2);
			}
			tx1 = x1 - walk[i][0];
			ty1 = y1 - walk[i][1];
			tx2 = x2 + walk[i][0];
			ty2 = y2 + walk[i][1];//其中一边遇到障碍不移动
			if (In(x1, y1) && In(tx2, ty2) && mat[tx1][ty1] == '#' && mat[tx2][ty2] != '#' && stat[x1][y1][tx2][ty2] == -1) {
				Addline(x1, y1, tx2, ty2);
			}
			tx1 = x1 + walk[i][0];
			ty1 = y1 + walk[i][1];
			tx2 = x2 - walk[i][0];
			ty2 = y2 - walk[i][1];//其中一边遇到障碍不移动
			if (In(tx1, ty1) && In(x2, y2) && mat[tx1][ty1] != '#' && mat[tx2][ty2] == '#' && stat[tx1][ty1][x2][y2] == -1) {
				Addline(tx1, ty1, x2, y2);
			}
		}
	}
}

int Getfa(int p)//并查集找父亲
{
	if (fa[p] == p) return p;
	return fa[p] = Getfa(fa[p]);
}

void Link(int x, int y)//并查集链接
{
	Getfa(x);
	Getfa(y);
	if (fa[x] == fa[y]) return;
	if (rak[fa[x]] > rak[fa[y]]) fa[fa[y]] = fa[x];
	else if (rak[fa[x]] < rak[fa[y]]) fa[fa[x]] = fa[y];
	else ++rak[fa[x]], fa[fa[y]] = fa[x];
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

int Solve()
{
	int Ans = 0, total = 0;
	for (int i = 1; i <= n * m; ++i) fa[i] = i;
	memset(stat, -1, sizeof(stat));
	lt = lh = 0;
	for (int i = 1; i <= n; ++i) {//先Bfs搜索出那些从那些点对出发是可以使得其中一个掉落的
		for (int j = 1; j <= m; ++j) {
			if (mat[i][j] != '.') continue;
			for (int k = 0; k <= n + 1; ++k) {
				Addline(i, j, k, 0);
				Addline(i, j, k, m + 1);
			}
			for (int k = 0; k <= m + 1; ++k) {
				Addline(i, j, 0, k);
				Addline(i, j, n + 1, k);
			}
		}
	}
	Bfs();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			for (int k = 1; k <= n; ++k) {
				for (int q = 1; q <= m; ++q) {
					if (mat[i][j] == '.' && mat[k][q] == '.' && (stat[i][j][k][q] == -1 && stat[k][q][i][j] == -1)) {
						Link(Gettip(i, j), Gettip(k, q));//将不可能可行的点对用并查集连接，归为一个等价类
					}
				}
			}
		}
	}
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (mat[i][j] == '.') {
				++cnt[Getfa(Gettip(i, j))];//统计每个等价类的大小
			}
		}
	}
	for (int i = 1; i <= n * m; ++i) {//只要选择的点集不都在一个等价类之中即可
		total += cnt[i];
		Ans = (Ans + Pow(2, cnt[i])) % mod;
		Ans = (Ans - 1 + mod) % mod;
	}
	Ans = (Ans + 1) % mod;
	Ans = (Pow(2, total) - Ans + mod) % mod;
	return Ans;
}

class CoinsGame {
    public:
    int ways(vector<string> board) {
		Init(board);//读入
		return Solve();
    }
};

