#include <algorithm>
using namespace std;
struct Edge
{
	int v;
	Edge *next;
};
int mc;
Edge memory[200], *edge[100];
long long f[40][40][40], g[40][40][40];
class CentaurCompany
{
public:
	int n;
	void AddEdge(int u, int v)
	{
		Edge *p = &memory[mc++], *q = &memory[mc++];
		p->v = v, p->next = edge[u];
		q->v = u, q->next = edge[v];
		edge[u] = p, edge[v] = q;
	}
	void Dfs(int node, int last)
	{
		f[node][0][0] = g[node][0][0] = 1;
		for(Edge *next = edge[node]; next; next = next->next)
		{
			if(next->v != last)
			{
				Dfs(next->v, node);
				for(int i = n; i >= 0; i--) //合并子树 
				{
					for(int j = n; j >= 0; j--)
					{
						long long sumf = 0, sumg = 0;
						for(int u = 0; u <= i; u++)
						{
							for(int v = 0; v <= j; v++)
							{
								sumf += f[next->v][u][v] * f[node][i - u][j - v];
								sumg += g[next->v][u][v] * g[node][i - u][j - v];
							}
						}
						f[node][i][j] = sumf;
						g[node][i][j] = sumg;
					}
				}
			}
		}
		for(int i = n; i >= 0; i--) //树形dp 
		{
			for(int j = n; j >= 0; j--)
			{
				g[node][i][j] = f[node][i][j];
				if(i && j)
					f[node][i][j] += g[node][i - 1][j - 1];
				if(i)
					g[node][i][j] += g[node][i - 1][j];
			}
		}
	}
	double getvalue(vector<int> u, vector<int> v)
	{
		n = u.size() + 1;
		for(int i = 0; i < u.size(); i++)
			AddEdge(--u[i], --v[i]);
		Dfs(0, -1);
		long long ans = 0;
		for(int i = 0; i <= n; i++) //代价由点数及连通块数确定 
		{
			for(int j = 0; j <= n; j++)
				ans += f[0][i][j] * max(j * 2 - i - 2, 0);
		}
		return (double)ans / (double)(1LL << (n - 1));
	}
};
