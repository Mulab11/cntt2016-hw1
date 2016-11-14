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
const int MAXN = 60, MAXM = 6060, oo = 1010101010;
class Edge
{
	public:
		int to, v, next;
};
Edge e[MAXM];
int head[MAXN], en = 1, start[MAXN], height[MAXN], S, T;
void insert(int u, int v, int w, int w2 = 0)
{
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
class OldBridges
{
	private:
	void buildGraph(vector <string> bridges)
	{
		memset(head, -1, sizeof(head));
		en = 1;
		S = bridges.size();
		T = S + 1;
		for(int i = 0; i < bridges.size(); i++)
			for(int j = i + 1; j < bridges.size(); j++)
				if(bridges[i][j] == 'O')
					insert(i, j, 2, 2);
				else if(bridges[i][j] == 'N')
					insert(i, j, oo, oo);
	}
	public:
	string isPossible(vector<string> bridges, int a1, int a2, int an, int b1, int b2, int bn)
	{
		//maximum multi-commodity flow problem...
		//we can solve it by running the maximum "even" flow twice
		buildGraph(bridges);
		insert(S, a1, an * 2);
		insert(a2, T, an * 2);
		insert(S, b1, bn * 2);
		insert(b2, T, bn * 2);
		if(dinic() != an * 2 + bn * 2)
			return "No";
		buildGraph(bridges);
		insert(S, a1, an * 2);
		insert(a2, T, an * 2);
		insert(S, b2, bn * 2);//reverse b
		insert(b1, T, bn * 2);
		if(dinic() != an * 2 + bn * 2)
			return "No";
		return "Yes";
	}
};

