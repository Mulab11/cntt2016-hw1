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
const int MAXN = 15151, MAXM = 1010101, oo = 1010101010;
class Edge
{
	public:
		int to, v, next;
};
Edge e[MAXM];
int head[MAXN], en = 1, start[MAXN], height[MAXN], S, T;
void clearedge()
{
	memset(head, -1, (T + 1) * sizeof(int));
	en = 1;
}
void insert(int u, int v, int w, int w2 = 0)
{
	if(!w)
		return;
	e[++en].to = v;
	e[en].v = w;
	e[en].next = head[u];
	head[u] = en;
	e[++en].to = u;
	e[en].v = w2;
	e[en].next = head[v];
	head[v] = en;
}
bool bfs()
{
	static queue <int> q;
	memset(height, 63, (T + 1) * sizeof(int));
	height[S] = 0;
	q.push(S);
	while(!q.empty())
	{
		int now = q.front();
		q.pop();
		for(int i = head[now]; i > 0; i = e[i].next)
			if(e[i].v && height[e[i].to] > height[now] + 1)
			{
				height[e[i].to] = height[now] + 1;
				q.push(e[i].to);
			}
	}
	return height[T] < oo;
}
int dfs(int p, int maxflow)
{
	if(p == T)
		return maxflow;
	int allflow = maxflow;
	for(int &i = start[p]; i > 0; i = e[i].next)
		if(e[i].v && height[e[i].to] > height[p])
		{
			int tmp = dfs(e[i].to, e[i].v < maxflow ? e[i].v : maxflow);
			e[i].v -= tmp;
			e[i ^ 1].v += tmp;
			if(!(maxflow -= tmp))
				break;
		}
	return allflow - maxflow;
}
int dinic()
{
	int allflow = 0;
	while(bfs())
	{
		memcpy(start, head, (T + 1) * sizeof(int));
		allflow += dfs(S, oo);
	}
	return allflow;
}
class BoardPainting
{
public:
	int minimalSteps(vector<string> target)
	{
		int n = target.size(), m = target[0].size();
		S = n * m;
		T = S + 1;
		clearedge();
		#define isblack(x, y) ((x) >= 0 && (x) < n && (y) >= 0 && (y) < m && target[x][y] == '#')
		for(int i = 0; i < n; i++)//build graph
			for(int j = 0; j < m; j++)
				if(isblack(i, j))
				{
					const int now = i * m + j;
					insert(S, now, 2 - isblack(i - 1, j) - isblack(i + 1, j));
					if(isblack(i, j + 1))
						insert(now, now + 1, 1, 1);
					if(isblack(i + 1, j))
						insert(now, now + m, 1, 1);
					insert(now, T, 2 - isblack(i, j - 1) - isblack(i, j + 1));
				}
		return dinic() / 2;//min cut must be even
	}
};

