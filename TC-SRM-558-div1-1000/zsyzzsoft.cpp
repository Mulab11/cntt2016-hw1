#include <algorithm>
using namespace std;
const int inf = 2147483647;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
struct Edge
{
	int v, f;
	Edge *next, *rest;
};
int mc, level[1000], que[1000];
Edge memory[10000], *edge[1000];
class SurroundingGame
{
public:
	int n, m, s, t;
	int Conv(char c)
	{
		if(c >= '0' && c <= '9')
			return c - '0';
		if(c >= 'a' && c <= 'z')
			return c - 'a' + 10;
		return c - 'A' + 36;
	}
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
	int maxScore(vector<string> cost, vector<string> benefit)
	{
		n = cost.size(), m = cost[0].size();
		s = n * m * 2, t = s + 1;
		int ans = 0;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				ans += Conv(benefit[i][j]);
				AddEdge(i * m + j, i * m + j + n * m, Conv(benefit[i][j])); //放弃 
				if((i + j) & 1)
				{
					AddEdge(s, i * m + j, Conv(cost[i][j])); //放棋子 
					for(int k = 0; k < 4; k++) //被包围 
					{
						int ni = i + dx[k], nj = j + dy[k];
						if(ni >= 0 && ni < n && nj >= 0 && nj < m)
							AddEdge(i * m + j + n * m, ni * m + nj + n * m, inf);
					}
				}
				else
				{
					AddEdge(i * m + j + n * m, t, Conv(cost[i][j])); //放棋子 
					for(int k = 0; k < 4; k++) //被包围 
					{
						int ni = i + dx[k], nj = j + dy[k];
						if(ni >= 0 && ni < n && nj >= 0 && nj < m)
							AddEdge(ni * m + nj, i * m + j, inf);
					}
				}
			}
		}
		while(MakeLevel())
			ans -= Dfs(s, inf);
		return ans;
	}
};
