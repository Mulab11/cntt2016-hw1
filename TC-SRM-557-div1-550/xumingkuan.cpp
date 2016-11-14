#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;
class Edge2
{
	public:
		int to, next;
};
Edge2 e1[10101];
int h1[53];
int num1;
bool e0[53][53];
bool alive[53];
void insert1(int u, int v)
{
	e1[++num1].to = v;
	e1[num1].next = h1[u];
	h1[u] = num1;
	e0[u][v] = true;
}
class Edge
{
	public:
		int to, v, next;
};
Edge e[2010101];
int edgenum;
int s, t, n, m;
int height[111], head[111], start[111], ans;
queue <int> q;
bool bfs()
{
	memset(height, 1, sizeof(height));
	height[s] = 0;
	q.push(s);
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		for(int i = head[p]; i > 0; i = e[i].next)
		{
			if(e[i].v > 0 && height[e[i].to] > height[p] + 1)
			{
				height[e[i].to] = height[p] + 1;
				q.push(e[i].to);
			}
		}
	}
	return height[t] != 16843009;
}
int dfs(int p, int maxflow)
{
	if(p == t)
		return maxflow;
	int allflow = maxflow;
	for(int &i = start[p]; i > 0; i = e[i].next)
	{
		if(e[i].v > 0 && height[e[i].to] > height[p])
		{
			int tmp = dfs(e[i].to, maxflow > e[i].v ? e[i].v : maxflow);
			e[i].v -= tmp;
			e[i ^ 1].v += tmp;
			maxflow -= tmp;
			if(!maxflow)
				break;
		}
	}
	return allflow - maxflow;
}
int dinic()
{
	int allflow = 0;
	while(bfs())
	{
		for(int i = 1; i <= t; i++)
			start[i] = head[i];
		allflow += dfs(s, 2147483647);
	}
	return allflow;
}
void insert(int u, int w, int v1)
{
	e[++edgenum].to = w + n;
	e[edgenum].v = v1;
	e[edgenum].next = head[u];
	head[u] = edgenum;
	e[++edgenum].to = u;
	e[edgenum].v = 0;
	e[edgenum].next = head[w + n];
	head[w + n] = edgenum;
}
void insert(int u, int w)
{
	e[++edgenum].to = w;
	e[edgenum].v = 1;
	e[edgenum].next = head[u];
	head[u] = edgenum;
	e[++edgenum].to = u;
	e[edgenum].v = 0;
	e[edgenum].next = head[w];
	head[w] = edgenum;
}
bool visit[53];
bool find_circle(int u, int p)
{
	if(visit[p] && u == p)
		return true;
	if(visit[p])
		return false;
	visit[p] = true;
	for(int i = h1[p]; i > 0; i = e1[i].next)
		if(find_circle(u, e1[i].to))
			return true;
	return false;
}
void dfs2(int u, int p)
{
	visit[p] = true;
	for(int i = h1[p]; i > 0; i = e1[i].next)
		if(!visit[e1[i].to])
		{
			if(alive[e1[i].to])
				insert(u, e1[i].to, 1);
			dfs2(u, e1[i].to);
		}
}
class Incubator
{
	public:
	int maxMagicalGirls(vector<string> love)
	{
		n = love.size();
		memset(h1, 0, sizeof(h1));
		memset(e0, false, sizeof(e0));
		memset(head, 0, sizeof(head));
		num1 = edgenum = 1;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(love[i - 1][j - 1] == 'Y')
					insert1(i, j);
		for(int i = 1; i <= n; i++)
		{
			memset(visit, false, sizeof(visit));
			alive[i] = !find_circle(i, i);//if find_circle(i, i), turning i into magical girl would make i protected, so we'd better not do that
		}
		for(int i = 1; i <= n; i++)
			if(alive[i])
			{
				memset(visit, false, sizeof(visit));
				dfs2(i, i);//build graph: i -> j + n (i -> ... -> j)
			}
		s = n + n + 1;
		t = n + n + 2;
		ans = 0;
		for(int i = 1; i <= n; i++)
			if(alive[i])
			{
				insert(s, i);
				insert(i + n, t);//build graph: s -> i, i + n -> t
				ans++;
			}
		ans -= dinic();
		return ans;
	}
};

