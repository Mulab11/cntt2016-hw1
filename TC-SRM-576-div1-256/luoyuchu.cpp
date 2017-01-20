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
bool vis[maxn][maxn];
int Midval;

void Dfs(int x, int y)//Dfs检查是否可以到达
{
	if (vis[x][y] == 1) return;
	vis[x][y] = 1;
	if (y > 1 && mat[x][y - 1]) Dfs(x, y - 1);
	if (y < m && mat[x][y + 1]) Dfs(x, y + 1);
	for (int i = 1; i <= Midval; ++i) {
		if (x - i <= 0) break;
		if (mat[x - i][y]) {
			Dfs(x - i, y);
		}
	}
	for (int i = 1; i <= Midval; ++i) {
		if (x + i > n) break;
		if (mat[x + i][y]) {
			Dfs(x + i, y);
		}
	}
}

class ArcadeManao {
    public:
    int shortestLadder(vector<string> level, int cx, int cy) {
		n = level.size();
		m = level[0].length();
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				mat[i][j] = (level[i - 1][j - 1] == 'X');
			}
		}
		int l = 0, r = n;
		while (l != r) {//二分梯子的长度，然后Dfs检查是否可以到达
			Midval = (l + r) / 2;
			memset(vis, 0, sizeof(vis));
			Dfs(n, 1);
			if (vis[cx][cy] == 1) r = Midval;
			else l = Midval + 1;
		}
        return l;
    }
};

