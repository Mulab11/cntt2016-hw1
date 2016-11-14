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

const int MAXN = 1010, MAXM = 10101, oo = 1010101010;
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
/*
          cost         benefit
  +-----------------+ +-------+
 /  benefit    inf  V/ benefit \
+ +-------->O------>O---------+ +
|/          |       |          \V
S           |inf    |inf        T
|\  benefit V  inf  V  benefit /^
+ +-------->O------>O---------+ +
 \  benefit ^\      cost       /
  +---------+ +---------------+

ans = \sum{benefit * 2} - mincut.
*/
class SurroundingGame
{
	private:
	int decode(char ch)
	{
		if(isdigit(ch))
			return ch - '0';
		if(islower(ch))
			return ch - 'a' + 10;
		if(isupper(ch))
			return ch - 'A' + 36;
		return -1;
	}
	public:
	int maxScore(vector<string> cost, vector<string> benefit)
	{
		const int n = cost.size(), m = cost[0].size();
		S = n * m * 2 + 1;
		T = S + 1;
		clearedge();
		int ans = 0;
		for(int i = 0; i < n; i++)//build graph
			for(int j = 0; j < m; j++)
			{
				const int nowPoint = i * m + j + 1, nowPoint2 = i * m + j + 1 + n * m, nowCost = decode(cost[i][j]), nowBenefit = decode(benefit[i][j]);
				ans += nowBenefit * 2;
				insert(S, nowPoint, nowBenefit);
				insert(nowPoint, nowPoint2, oo);
				insert(nowPoint2, T, nowBenefit);
				if((i ^ j) & 1)//odd
				{
					insert(S, nowPoint2, nowCost);
					if(i)
					{
						insert(nowPoint, nowPoint - m, oo);
						insert(nowPoint2, nowPoint2 - m, oo);
					}
					if(i != n - 1)
					{
						insert(nowPoint, nowPoint + m, oo);
						insert(nowPoint2, nowPoint2 + m, oo);
					}
					if(j)
					{
						insert(nowPoint, nowPoint - 1, oo);
						insert(nowPoint2, nowPoint2 - 1, oo);
					}
					if(j != m - 1)
					{
						insert(nowPoint, nowPoint + 1, oo);
						insert(nowPoint2, nowPoint2 + 1, oo);
					}
				}
				else//even
					insert(nowPoint, T, nowCost);
			}
		ans -= dinic();
		return ans;
	}
};

