#include <algorithm>
using namespace std;
class Incubator
{
public:
	int n, s, t;
	int f[200][200], level[200], que[200];
	bool con[50][50];
	void AddEdge(int u, int v)
	{
		f[u][v]++;
	}
	bool MakeLevel()
	{
		for(int i = 0; i <= t; i++)
			level[i] = -1;
		que[0] = s;
		level[s] = 0;
		for(int l = 0, r = 1; l < r; l++)
		{
			int cur = que[l];
			for(int i = 0; i <= t; i++)
			{
				if(f[cur][i] && level[i] == -1)
					level[que[r++] = i] = level[cur] + 1;
			}
		}
		return level[t] >= 0;
	}
	int Dfs(int node, int flow)
	{
		if(node == t)
			return flow;
		int ret = 0;
		for(int i = 0; i <= t && flow; i++)
		{
			if(level[node] + 1 == level[i] && f[node][i])
			{
				int tmp = Dfs(i, min(flow, f[node][i]));
				f[node][i] -= tmp;
				f[i][node] += tmp;
				flow -= tmp;
				ret += tmp;
			}
		}
		if(!ret)
			level[node] = -1;
		return ret;
	}
	int maxMagicalGirls(vector<string> love)
	{
		n = love.size();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				con[i][j] = love[i][j] == 'Y';
		}
		for(int k = 0; k < n; k++) //传递闭包
		{
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
					con[i][j] |= con[i][k] & con[k][j];
			}
		}
		s = n * 2, t = s + 1; //建图
		for(int i = 0; i < n; i++)
		{
			AddEdge(s, i);
			AddEdge(i + n, t);
			for(int j = 0; j < n; j++)
			{
				if(con[i][j])
					AddEdge(i, j + n);
			}
		}
		int ans = n; //网络流
		while(MakeLevel())
			ans -= Dfs(s, 2147483647);
		return ans;
	}
};