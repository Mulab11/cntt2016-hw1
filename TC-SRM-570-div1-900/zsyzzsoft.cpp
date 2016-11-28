#include <algorithm>
using namespace std;
const int inf = 2147483647;
struct Edge
{
	int v, f, w;
	Edge *next, *rest;
};
int mc, dis[2000], pre[2000], flow[2000], que[4000000];
bool vis[2000];
Edge memory[16000], *edge[2000], *path[2000];
class CurvyonRails
{
public:
	int s, t;
	void AddEdge(int u, int v, int f, int w = 0)
	{
		Edge *p = &memory[mc++], *q = &memory[mc++];
		p->v = v, p->f = f, p->w = w, p->next = edge[u], p->rest = q;
		q->v = u, q->f = 0, q->w = -w, q->next = edge[v], q->rest = p;
		edge[u] = p, edge[v] = q;
	}
	int SPFA()
	{
		for(int i = 0; i <= t; i++)
			dis[i] = inf, path[i] = NULL;
		que[0] = s;
		dis[s] = 0;
		flow[s] = inf;
		vis[s] = true;
		for(int l = 0, r = 1; l < r; l++)
		{
			int cur = que[l];
			for(Edge *next = edge[cur]; next; next = next->next)
			{
				if(next->f && dis[cur] + next->w < dis[next->v])
				{
					dis[next->v] = dis[cur] + next->w;
					pre[next->v] = cur;
					path[next->v] = next;
					flow[next->v] = min(flow[cur], next->f);
					if(!vis[next->v])
						vis[que[r++] = next->v] = true;
				}
			}
			vis[cur] = false;
		}
		if(!path[t])
			return false;
		int f = flow[t];
		for(int i = t; i != s; i = pre[i])
			path[i]->f -= f, path[i]->rest->f += f;
		return f;
	}
	int getmin(vector<string> field)
	{
		int n = field.size(), m = field[0].size();
		s = n * m * 3, t = s + 1;
		int tota = 0, totb = 0;
		for(int i = 0; i < n; i++) //建图 
		{
			for(int j = 0; j < m; j++)
			{
				if(field[i][j] == 'w')
					continue;
				if((i + j) & 1)
				{
					tota += 2;
					AddEdge(i * m + j, t, 2);
					AddEdge(i * m + j + n * m, i * m + j, 1, 0);
					AddEdge(i * m + j + n * m, i * m + j, 1, field[i][j] == 'C');
					AddEdge(i * m + j + n * m * 2, i * m + j, 1, 0);
					AddEdge(i * m + j + n * m * 2, i * m + j, 1, field[i][j] == 'C');
				}
				else
				{
					totb += 2;
					AddEdge(s, i * m + j, 2);
					AddEdge(i * m + j, i * m + j + n * m, 1, 0);
					AddEdge(i * m + j, i * m + j + n * m, 1, field[i][j] == 'C');
					AddEdge(i * m + j, i * m + j + n * m * 2, 1, 0);
					AddEdge(i * m + j, i * m + j + n * m * 2, 1, field[i][j] == 'C');
					if(i)
						AddEdge(i * m + j + n * m, (i - 1) * m + j + n * m, 1);
					if(i + 1 < n)
						AddEdge(i * m + j + n * m, (i + 1) * m + j + n * m, 1);
					if(j)
						AddEdge(i * m + j + n * m * 2, i * m + (j - 1) + n * m * 2, 1);
					if(j + 1 < m)
						AddEdge(i * m + j + n * m * 2, i * m + (j + 1) + n * m * 2, 1);
				}
			}
		}
		if(tota != totb)
			return -1;
		int ans = 0;
		for(int f; (f = SPFA()) > 0; tota -= f, ans += f * dis[t]); //费用流 
		return tota ? -1 : ans;
	}
};
