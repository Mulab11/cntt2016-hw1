#include <algorithm>
using namespace std;
const int inf = 2147483647;
struct Edge
{
	int v, f;
	Edge *next, *rest;
};
int mc, level[5000], que[5000];
Edge memory[50000], *edge[5000];
class GearsDiv1
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
	int Work(const string &color, const vector<string> &graph, char a, char b)
	{
		int n = color.size(), flow = 0;
		s = n, t = n + 1;
		mc = 0;
		for(int i = 0; i <= t; i++)
			edge[i] = NULL;
		for(int i = 0; i < n; i++)
		{
			if(color[i] == a)
				AddEdge(s, i, 1);
			else if(color[i] == b)
				AddEdge(i, t, 1);
		}
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(graph[i][j] == 'Y' && color[i] == a && color[j] == b) //只有同向颜色间有约束 
					AddEdge(i, j, 1);
			}
		}
		while(MakeLevel()) //最大独立集
			flow += Dfs(s, inf);
		return flow;
	}
	int getmin(string color, vector<string> graph)
	{
		return min(Work(color, graph, 'R', 'G'), min(Work(color, graph, 'R', 'B'), Work(color, graph, 'G', 'B'))); //枚举哪两种颜色同向 
	}
};