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

int n, m, D;
char mat[maxn][maxn];
int color[maxn][maxn];
int Index;
int item[maxn * maxn], total = 0;
int f[2][2];

void Dfs(int x, int y)
{
	static int tx, ty;
	color[x][y] = Index;
	++item[total];
	for (int i = -D; i <= D; ++i) {
		for (int j = -(D - abs(i)); j <= (D - abs(i)); ++j) {
			tx = x + i;
			ty = y + j;
			if (tx >= 1 && tx <= n && ty >= 1 && ty <= m && color[tx][ty] == 0 && mat[tx][ty] == 'v') {
				Dfs(tx, ty);
			}
		}
	}
}

int Solve()
{
	total = 0;
	Index = 0;
	memset(color, 0, sizeof(color));
	for (int i = 1; i <= n; ++i) {//先搜索出所有可以通过曼哈顿距离小于等于dist而链接的联通块，每一块一定全部是鸭子/鹅
		for (int j = 1; j <= m; ++j) {
			if (mat[i][j] == 'v' && color[i][j] == 0) {
				++Index;
				++total;
				item[total] = 0;
				Dfs(i, j);
				item[total] &= 1;
			}
		}
	}
	int nt = 0;
	memset(f, 0, sizeof(f));
	f[nt][0] = 1;
	for (int i = 1; i <= total; ++i) {//然后Dp求出选择鹅的总个数为偶数的方案
		memset(f[nt ^ 1], 0, sizeof(f[nt ^ 1]));
		for (int j = 0; j < 2; ++j) {
			(f[nt ^ 1][j ^ item[i]] += f[nt][j]) %= mod;
			(f[nt ^ 1][j] += f[nt][j]) %= mod;
		}
		nt ^= 1;
	}
	return (f[nt][0] - 1 + mod) % mod;//减去一个都不选的方案
}

class GooseInZooDivOne {
    public:
    int count(vector<string> field, int dist) {
		n = field.size();
		m = field[0].length();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				mat[i + 1][j + 1] = field[i][j];
			}
		}
		D = min(n + m - 2, dist);
		return Solve();//返回答案
    }
};
