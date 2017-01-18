#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;
const int MAXN = 1616, MAXM = 202020, oo = 1010101010;
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
void insert(int u, int v, int w)
{
	e[++en].to = v;
	e[en].v = w;
	e[en].next = head[u];
	head[u] = en;
	e[++en].to = u;
	e[en].v = 0;
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

class FoxAndCity
{
private:
	int n;
	int sqr(int x)
	{
		return x * x;
	}
public:
	int minimalCost(vector<string> linked, vector<int> want)
	{
		n = want.size();
		S = n * (n - 1) + 1;
		T = S + 1;
		clearedge();
		for(int i = 0; i < n; i++)
		{
			insert(S, i * (n - 1) + 1, i ? oo : sqr(want[i]));//dist[i] => 0 //dist[i(i!=0)] must not be 0
			for(int k = 2; k < n; k++)
				insert(i * (n - 1) + k - 1, i * (n - 1) + k, i ? sqr(want[i] - k + 1) : oo);//dist[i] => k-1 //dist[0] must be 0
			insert(i * (n - 1) + n - 1, T, i ? sqr(want[i] - n + 1) : oo);//dist[i] => n-1 //dist[0] must be 0
		}
		for(int i = 0; i < n; i++)//build graph
			for(int j = 0; j < n; j++)
				if(linked[i][j] == 'Y')
					for(int k = 2; k < n; k++)
						insert(i * (n - 1) + k, j * (n - 1) + k - 1, oo);
		return dinic();//min cut
	}
};

