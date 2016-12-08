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
class BoardPainting
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
	int minimalSteps(vector<string> board)
	{
		int n = board.size(), m = board[0].size();
		s = n * m, t = s + 1;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(board[i][j] == '.')
					continue;
				int flag[4] = {0};
				for(int k = 0; k < 4; k++)
				{
					int ni = i + dx[k], nj = j + dy[k];
					if(ni >= 0 && ni < n && nj >= 0 && nj < m && board[ni][nj] == '#')
						AddEdge(i * m + j, ni * m + nj, 1);
					else
						flag[k] = 1;
				}
				AddEdge(s, i * m + j, flag[0] + flag[1]); //纵向染色 
				AddEdge(i * m + j, t, flag[2] + flag[3]); //横向染色 
			}
		}
		int ans = 0;
		while(MakeLevel()) //最小割 
			ans += Dfs(s, inf);
		return ans / 2;
	} 
};