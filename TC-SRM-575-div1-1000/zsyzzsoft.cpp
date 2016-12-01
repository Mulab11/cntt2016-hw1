#include <algorithm>
using namespace std;
const int inf = 2147483647;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
struct Edge
{
	int v, f;
	Edge *next, *rest;
};
int mc, level[5000], que[5000];
Edge memory[50000], *edge[5000];
class TheTilesDivOne
{
public:
	int n, m, s, t;
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
	int find(vector<string> board)
	{
		n = board.size(), m = board[0].size();
		s = n * m * 2, t = s + 1;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(board[i][j] == 'X')
					continue;
				if((i + j) & 1)
				{
					if(i & 1) //起始点 
					{
						AddEdge(s, i * m + j, 1);
						for(int k = 0; k < 4; k++)
						{
							int u = i + dx[k], v = j + dy[k];
							if(u >= 0 && u < n && v >= 0 && v < m && board[u][v] == '.')
								AddEdge(i * m + j, u * m + v, 1);
						}
					}
					else //结束点 
					{
						AddEdge(i * m + j, t, 1);
						for(int k = 0; k < 4; k++)
						{
							int u = i + dx[k], v = j + dy[k];
							if(u >= 0 && u < n && v >= 0 && v < m && board[u][v] == '.')
								AddEdge(u * m + v + n * m, i * m + j, 1);
						}
					}
				}
				else //中间点，拆点限流 
					AddEdge(i * m + j, i * m + j + n * m, 1);
			}
		}
		int ans = 0;
		while(MakeLevel())
			ans += Dfs(s, inf);
		return ans;
	}
};