#include <algorithm>
#include <memory.h>
using namespace std;
const int inf = 2147483647;
struct Edge
{
	int v, f, w;
	Edge *next, *rest;
};
struct Tree
{
	int v;
	Tree *next;
};
int ans, tmc, mc, s, t, f[51][51][51][51], dis[2000], pre[2000], flow[2000], que[4000000];
bool vis[2000];
Edge memory[16000], *edge[2000], *path[2000];
Tree tmem[100], *tree[51];
bool col[51];
class DeerInZooDivOne
{
public:
	int n, m;
	void AddTreeEdge(int u, int v)
	{
		Tree *p = &tmem[tmc++], *q = &tmem[tmc++];
		p->v = v, p->next = tree[u];
		q->v = u, q->next = tree[v];
		tree[u] = p, tree[v] = q;
	}
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
	void Color(int node)
	{
		col[node] = true;
		for(Tree *next = tree[node]; next; next = next->next)
		{
			if(!col[next->v])
				Color(next->v);
		}
	}
	void Clear(int u, int pu, int v, int pv)
	{
		if(!f[u][pu][v][pv])
			return;
		f[u][pu][v][pv] = 0;
		for(Tree *p = tree[u]; p; p = p->next)
		{
			if(p->v == pu)
				continue;
			for(Tree *q = tree[v]; q; q = q->next)
			{
				if(q->v == pv)
					continue;
				Clear(p->v, u, q->v, v);
			}
		}
	}
	int Dfs(int u, int pu, int v, int pv)
	{
		if(f[u][pu][v][pv])
			return f[u][pu][v][pv];
		for(Tree *p = tree[u]; p; p = p->next)
		{
			if(p->v == pu)
				continue;
			for(Tree *q = tree[v]; q; q = q->next)
			{
				if(q->v == pv)
					continue;
				Dfs(p->v, u, q->v, v); //计算任意两棵子树的最大同构 
			}
		}
		mc = 0;
		for(int i = 0; i <= t; i++)
			edge[i] = NULL;
		for(Tree *p = tree[u]; p; p = p->next) //最大子树匹配 
		{
			if(p->v == pu)
				continue;
			for(Tree *q = tree[v]; q; q = q->next)
			{
				if(q->v == pv)
					continue;
				AddEdge(p->v, q->v, 1, -f[p->v][u][q->v][v]);
			}
		}
		for(Tree *p = tree[u]; p; p = p->next)
		{
			if(p->v != pu)
				AddEdge(s, p->v, 1);
		}
		for(Tree *q = tree[v]; q; q = q->next)
		{
			if(q->v != pv)
				AddEdge(q->v, t, 1);
		}
		f[u][pu][v][pv] = 1; //费用流 
		for(int flow; (flow = SPFA()) > 0; f[u][pu][v][pv] -= flow * dis[t]);
		return f[u][pu][v][pv];
	}
	int getmax(vector<int> eu, vector<int> ev)
	{
		m = eu.size(), n = m + 1;
		s = n, t = n + 1;
		for(int i = 0; i < m; i++) //把整棵树分成两部分 
		{
			tmc = 0;
			memset(tree, 0, sizeof(tree));
			for(int j = 0; j < m; j++)
			{
				if(j != i) //删除一条边 
					AddTreeEdge(eu[j], ev[j]);
			}
			memset(col, 0, sizeof(col));
			Color(0);
			for(int u = 0; u < n; u++) //枚举两棵树的根节点 
			{
				for(int v = 0; v < n; v++)
				{
					if(!col[u] && col[v])
						ans = max(ans, Dfs(u, u, v, v));
				}
			}
			for(int u = 0; u < n; u++) //清除记忆化数组 
			{
				for(int v = 0; v < n; v++)
				{
					if(!col[u] && col[v])
						Clear(u, u, v, v);
				}
			}
		}
		return ans;
	}
};