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

int n, Root;
int mat[maxn][maxn];
int du[maxn], fa[maxn];
int f[maxn];//f[i]表示当前以i为根的子树内部可区分的最少灯塔数

void Dfs(int p)
{
	int cnt = 0;
	f[p] = 0;
	for (int i = 1; i <= n; ++i) {
		if (mat[p][i] == 0) continue;
		if (fa[p] == i) continue;
		fa[i] = p;
		Dfs(i);
		f[p] += f[i];
		cnt += (f[i] == 0);
	}
	if (cnt) f[p] += (cnt - 1);//最多存在一个子树中不放灯塔
}

int Solve()
{
	memset(fa, 0, sizeof(fa));
	Dfs(Root);//Dp
}

class TPS {
    public:
    int minimalBeacons(vector<string> linked) {
		n = linked.size();
		memset(du, 0, sizeof(du));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				mat[i][j] = (linked[i - 1][j - 1] == 'Y');
				du[i] += mat[i][j];
			}
		}
		if (n <= 1) return 0;//特殊情况
		Root = -1;
		for (int i = 1; i <= n; ++i) {
			if (du[i] > 2) {
				Root = i;
				break;
			}
		}
		if (Root == -1) return 1;//如果是一条链
		Solve();//Dp
		return f[Root];
    }
};
