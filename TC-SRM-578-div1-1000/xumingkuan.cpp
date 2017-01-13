#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <queue>
#include <map>
#include <set>
using namespace std;
const int MAXN = 10101, MAXM = 101010;
const long long oo = 101010101010101010ll;
class Edge
{
	public:
		int to, c, next;
		long long v;
};
Edge e[MAXM];
int head[MAXN], en = 1, start[MAXN], S, T;
long long height[MAXN];
long long cost = 0;
bool inque[MAXN];
void clearedge()
{
	memset(head, -1, (T + 1) * sizeof(int));
	en = 1;
}
void insert(int u, int v, long long w, int c)
{
	e[++en].to = v;
	e[en].v = w;
	e[en].c = c;
	e[en].next = head[u];
	head[u] = en;
	e[++en].to = u;
	e[en].v = 0;
	e[en].c = -c;
	e[en].next = head[v];
	head[v] = en;
}
bool spfa()
{
	static queue <int> q;
	memset(height, 63, sizeof(height));
	height[S] = 0;
	q.push(S);
	while(!q.empty())
	{
		int now = q.front();
		q.pop();
		inque[now] = false;
		for(int i = head[now]; i > 0; i = e[i].next)
			if(e[i].v && height[e[i].to] > height[now] + e[i].c)
			{
				height[e[i].to] = height[now] + e[i].c;
				if(!inque[e[i].to])
				{
					q.push(e[i].to);
					inque[e[i].to] = true;
				}
			}
	}
	return height[T] < oo;
}
long long dfs(int p, long long maxflow)
{
	if(p == T)
		return maxflow;
	long long allflow = maxflow;
	inque[p] = true;
	for(int &i = start[p]; i > 0; i = e[i].next)
		if(e[i].v && !inque[e[i].to] && height[e[i].to] == height[p] + e[i].c)
		{
			long long tmp = dfs(e[i].to, e[i].v < maxflow ? e[i].v : maxflow);
			cost += e[i].c * tmp;
			e[i].v -= tmp;
			e[i ^ 1].v += tmp;
			if(!(maxflow -= tmp))
				break;
		}
	inque[p] = false;
	return allflow - maxflow;
}
long long dinic()
{
	memset(inque, false, (T + 1) * sizeof(bool));
	long long allflow = 0;
	cost = 0;
	while(spfa())
	{
		if(height[T] >= 0)//qiu zui xiao fei yong ke xing liu
			break;
		memcpy(start, head, (T + 1) * sizeof(int));
		allflow += dfs(S, oo);
	}
	return allflow;
}
class Edge1
{
public:
	int to, next;
};
class DeerInZooDivOne
{
private:
	Edge1 e1[120];
	int head1[60], en1;
	int n;
	void insert1(int u, int v)
	{
		e1[++en1].to = v;
		e1[en1].next = head1[u];
		head1[u] = en1;
		e1[++en1].to = u;
		e1[en1].next = head1[v];
		head1[v] = en1;
	}
	int f[60][60];//f[i][j]: max size of isomorphic trees with roots i and j
	int cut;
	int ans;
	int lc[60], rs[60];//left child, right sibling
	bool visit[60];//for dfs
	int numson[60];
	bool mark[60];
	void dfs1(int p, bool type)//get lc, rs, numson
	{
		visit[p] = true;
		numson[p] = 0;
		lc[p] = -1;
		for(int i = head1[p]; i > 0; i = e1[i].next)
			if(!visit[e1[i].to] && e1[i].to != cut && (type || mark[e1[i].to]))
			{
				rs[e1[i].to] = lc[p];
				lc[p] = e1[i].to;
				numson[p]++;
				dfs1(e1[i].to, type);
			}
	}
	void solve(int u, int v)
	{
//		if(f[u][v] != -1)//we don't need memorization
//			return;
		for(int i = lc[u]; i >= 0; i = rs[i])
			for(int j = lc[v]; j >= 0; j = rs[j])
				solve(i, j);
		S = numson[u] + numson[v];
		T = S + 1;
		clearedge();
		for(int i = 0; i < numson[u]; i++)//build graph
			insert(S, i, 1, 0);
		for(int i = numson[u]; i < S; i++)
			insert(i, T, 1, 0);
		for(int i = lc[u], cnti = 0; i >= 0; i = rs[i], cnti++)
			for(int j = lc[v], cntj = numson[u]; j >= 0; j = rs[j], cntj++)
				insert(cnti, cntj, 1, -f[i][j]);//negative cost, then min cost will be max -cost
		dinic();
		f[u][v] = f[v][u] = 1 - cost;//add 1 for root(u and v)
		//printf("%d: f[%d][%d] = %d\n", cut, u, v, f[u][v]); //for debug
		if(f[u][v] > ans)
			ans = f[u][v];
	}
	void dfs2(int p)
	{
		mark[p] = true;
		for(int i = lc[p]; i >= 0; i = rs[i])
			dfs2(i);
	}
public:
	int getmax(vector<int> a, vector<int> b)
	{
		memset(head1, -1, sizeof(head1));
		en1 = 1;
		n = a.size() + 1;
		for(int i = 0; i < n - 1; i++)//build tree
			insert1(a[i], b[i]);
		for(int j = 0; j < n; j++)//enumerate the subtree to be cut (the first root)
		{
			cut = -1;//for dfs1(0);
			memset(visit, false, sizeof(visit));
			dfs1(0, true);
			cut = j;
			memset(mark, false, sizeof(mark));
			dfs2(cut);
			memset(visit, false, sizeof(visit));
			dfs1(cut, false);//can't dfs the points outside the subtree 'cut'
			for(int i = 0; i < n; i++)
				if(!mark[i])//i is not in subtree 'cut' (i is the second root)
				{
					//memset(f, -1, sizeof(f));
					memset(visit, false, sizeof(visit));
					dfs1(i, true);
					solve(cut, i);
				}
		}
		return ans;
	}
};

