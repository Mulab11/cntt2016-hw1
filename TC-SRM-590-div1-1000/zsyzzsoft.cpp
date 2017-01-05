#include <algorithm>
using namespace std;
const int inf = 2147483647;
struct Edge
{
	int v, f;
	Edge *next, *rest;
};
int mc, level[5000], que[5000];
Edge memory[500000], *edge[5000];
class FoxAndCity
{
public:
	int s, t;
	void AddEdge(int u, int v, int f)
	{
		Edge *p = &memory[mc++], *q = &memory[mc++];
		p->v = v, p->f = f, p->next = edge[u], p->rest = q;
		q->v = u, q->f = 0, q->next = edge[v], q->rest = p;
		edge[u] = p, edge[v] = q;
	}
	bool MakeLevel()
	{
		for(int i = 0; i <= t; i++)
			level[i] = -1;
		level[s] = 0;
		que[0] = s;
		for(int l = 0, r = 1; l < r; l++)
		{
			int cur = que[l];
			for(Edge *next = edge[cur]; next; next = next->next)
			{
				if(next->f && level[next->v] < 0)
					level[next->v] = level[cur] + 1, que[r++] = next->v;
			}
		}
		return level[t] >= 0;
	}
	int Dfs(int node, int maxf)
	{
		if(node == t)
			return maxf;
		int ret = 0;
		for(Edge *next = edge[node]; next && maxf; next = next->next)
		{
			if(next->f && level[node] + 1 == level[next->v])
			{
				int f = Dfs(next->v, min(maxf, next->f));
				next->f -= f;
				next->rest->f += f;
				maxf -= f;
				ret += f;
			}
		}
		if(!ret)
			level[node] = -1;
		return ret;
	}
	int minimalCost(vector<string> linked, vector<int> want)
	{
		int n = linked.size(), flow = 0;
		s = n * (n + 1), t = s + 1;
		for(int i = 0; i < n; i++)
		{
			AddEdge(s, i * (n + 1), inf);
			for(int j = 0; j < n; j++) //把每个点按每个距离值拆点 
				AddEdge(i * (n + 1) + j, i * (n + 1) + j + 1, !i ^ !j ? inf : (j - want[i]) * (j - want[i]));
			AddEdge(i * (n + 1) + n, t, inf);
		}
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(linked[i][j] == 'Y')
				{
					for(int k = 1; k <= n; k++) //有边相连的点距离差值不得超过1 
						AddEdge(i * (n + 1) + k, j * (n + 1) + k - 1, inf);
				}
			}
		}
		while(MakeLevel()) //最小割  
			flow += Dfs(s, inf);
		return flow;
	}
};