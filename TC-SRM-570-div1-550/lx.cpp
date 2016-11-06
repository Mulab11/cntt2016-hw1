#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define LX_JUDGE

using namespace std;
typedef long long LL;

const int N = 41;
const int D = 37;

LL f[N][N * 2][2];		// f 的定义见题解
LL g[N][N * 2];			// g : 辅助计算背包的转移

struct edge				//邻接表
{
	int to;
	edge *n;
} poolEdge[N * 2], *head[N], *cur = poolEdge;

inline void addEdge(int x, int y)
{
	cur->to = y, cur->n = head[x], head[x] = cur++;
	cur->to = x, cur->n = head[y], head[y] = cur++;
}

void Dfs(int x, int fa)
{
	for (edge *p = head[x]; p; p = p->n)	//递归计算子问题
	{
		if (p->to != fa)
			Dfs(p->to, x);
	}
	for (int col = 0; col < 2; ++col)		//枚举 x 的父亲选/不选
	{
		for (int a = 0; a < 2; ++a)			//枚举 x 选/不选
		{
			memset(g, 0, sizeof(g));
			int cnt = 0;
			if (a)
				g[0][D] = 1;
			else
				g[0][D + (col ? 1 : -1)] = 1;
			for (edge *p = head[x]; p; p = p->n)
			{
				int to = p->to;
				if (to == fa)
					continue ;
				rep (i, 0, D + D) if (f[to][i][a])  //背包转移，可以优化到 O(n^2)，但不是必要的
				{
					rep (j, 0, D + D) if (g[cnt][j])
						g[cnt + 1][i + j - D] += f[to][i][a] * g[cnt][j];		
				}
				++cnt;
			}
			rep (i, 0, D + D)
				f[x][i][col] += g[cnt][i];
		}
	}
}

class CentaurCompany
{
public:
	//树形DP，概率与期望
	double getvalue(vector<int> a, vector<int> b)
	{
		cur = poolEdge;
		memset(head, 0, sizeof(head));

		int n = a.size();
		rep (i, 0, n - 1)
			addEdge(a[i], b[i]);

		memset(f, 0, sizeof(f));
		Dfs(1, 0);

		double ans = 0;
		rep (i, 0, D + D)
			ans += (double) max(i - D - 2, 0) * f[1][i][1];		//统计答案

		ans /= 1ll << n;
		return ans;
	}
};

