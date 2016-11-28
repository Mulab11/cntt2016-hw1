#include <algorithm>
#include <memory.h>
using namespace std;
const int p = 1000000009;
class InducedSubgraphs
{
public:
	int n, root, c[50][50], dis[50][50], sz[50], f[50], g[50][50][50];
	void FindRoot(int node) //寻找树的重心，并计算子树大小 
	{
		int max_size = 0;
		sz[node] = 1;
		for(int i = 0; i < n; i++)
		{
			if(dis[node][i] == 1 && !sz[i])
			{
				FindRoot(i);
				max_size = max(max_size, sz[i]);
				sz[node] += sz[i];
			}
		}
		max_size = max(max_size, n - sz[node]);
		if(max_size <= n / 2)
			root = node;
	}
	void CalcF(int node)
	{
		f[node] = 1;
		int rest = sz[node] - 1;
		for(int i = 0; i < n; i++)
		{
			if(dis[node][i] == 1 && sz[i] < sz[node])
			{
				CalcF(i);
				f[node] = (long long)f[node] * c[rest][sz[i]] % p * f[i] % p;
				rest -= sz[i];
			}
		}
	}
	void CalcG(int node)
	{
		g[node][0][0] = 1;
		for(int i = 0; i < n; i++)
		{
			if(dis[node][i] == 1 && sz[i] < sz[node])
			{
				CalcG(i);
				for(int j = (n - 1) / 2; j >= 0; j--) //这是一个二维卷积 
				{
					for(int k = (n - 1) / 2; k >= 0; k--)
					{
						int sum = 0;
						for(int u = 0; u <= j; u++)
						{
							for(int v = 0; v <= k; v++)
								sum = ((long long)g[node][u][v] * g[i][j - u][k - v] % p * c[j][u] % p * c[k][v] % p + sum) % p;
						}
						g[node][j][k] = sum;
					}
				}
			}
		}
		g[node][sz[node]][0] = g[node][0][sz[node]] = f[node];
	}
	int getCount(vector<int> e_u, vector<int> e_v, int k)
	{
		n = e_u.size() + 1;
		c[0][0] = 1;
		for(int i = 1; i <= n; i++) //组合数 
		{
			c[i][0] = c[i][i] = 1;
			for(int j = 1; j < i; j++)
				c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
		}
		memset(sz, 0, sizeof(sz));
		memset(dis, 0x3F, sizeof(dis));
		for(int i = 0; i + 1 < n; i++)
			dis[e_u[i]][e_v[i]] = dis[e_v[i]][e_u[i]] = 1;
		for(int k = 0; k < n; k++) //任意两点路径长度 
		{
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
		root = -1;
		FindRoot(0); //计算重心 
		memset(sz, 0, sizeof(sz));
		FindRoot(root); //重新计算子树大小 
		for(int i = 0; i < n; i++) //处理树有两个重心的特殊情况 
		{
			if(sz[i] * 2 == n)
				sz[root] = n / 2;
		}
		for(int i = 0; i < n; i++)
		{
			if(i == root || sz[i] * 2 == n)
				CalcF(i); //f[i]表示i的子树中父亲的编号均比儿子大的方案数 
		}
		if(k == 1)
		{
			int ans = 1;
			for(int i = 1; i <= n; i++)
				ans = (long long)ans * i % p;
			return ans;
		}
		if(k * 2 <= n)
		{
			int ans = 0; //2k<=n时，中间的n-2k+2个点形成了一条链，重心一定在链上 
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
				{
					if(i != j && dis[i][j] == n - k * 2 + 1 && sz[i] == k && sz[j] == k)
						ans = ((long long)f[i] * f[j] + ans) % p; //链的两端独立 
				}
			}
			return ans;
		}
		memset(g, 0, sizeof(g));
		sz[root] = n; //2k>n时，重心一定存在于所有子集中 
		CalcG(root);
		int ans = g[root][n - k][n - k];
		for(int i = k * 2 - n; i; i--)
			ans = (long long)ans * i % p; //存在于所有子集中的点任意编号 
		return ans;
	}
};
