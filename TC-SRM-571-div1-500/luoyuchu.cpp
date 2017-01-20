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

const int maxn = 53;

int n, Db, Ans = 0;
int val[maxn];
int mat[maxn][maxn];
int e[maxn * maxn][2], et = 0;
bool fg[maxn] = {0};

void Dfs(int p, int dep)//考虑对于反图上找出一个最大独立集，所以不在最大独立集中的点一定是一个边的点覆盖，所以暴力搜索每条未被覆盖的边两端选择其一即可
{
	if (dep > Db) {
		return;//超过上限，终止搜索
	}
	if (p == et + 1) {
		static int s;
		s = 0;
		for (int i = 1; i <= n; ++i) {
			if (fg[i] == 0) {
				s += val[i];
			}
		}
		Ckmax(Ans, s);
		return;
	}
	if (fg[e[p][0]] || fg[e[p][1]]) Dfs(p + 1, dep);
	else {
		for (int j = 0; j < 2; ++j) {
			fg[e[p][j]] = 1;
			Dfs(p + 1, dep + 1);
			fg[e[p][j]] = 0;
		}
	}
}

class MagicMolecule {
public:
    int maxMagicPower(vector<int> magicPower, vector<string> magicBond) {
		n = magicPower.size();
		for (int i = 1; i <= n; ++i) val[i] = magicPower[i - 1];
		for (int i = 1; i <= n; ++i) {//建反图
			for (int j = 1; j <= n; ++j) {
				mat[i][j] = (magicBond[i - 1][j - 1] == 'N');
			}
		}
		et = 0;
		for (int i = 1; i <= n; ++i) {//取出反图的边
			for (int j = i + 1; j <= n; ++j) {
				if (mat[i][j]) {
					e[++et][0] = i;
					e[et][1] = j;
				}
			}
		}
		Db = n / 3;//设置上限
		Ans = -1;
		Dfs(1, 0);//暴力搜索
		return Ans;
	}
};

