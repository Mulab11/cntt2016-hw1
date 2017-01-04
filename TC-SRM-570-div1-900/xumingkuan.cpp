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
const int MAXN = 2020, MAXM = 10101, oo = 101010101;
class Edge
{
public:
	int to, v, c, next;
};
class CurvyonRails
{
private:
	Edge e[MAXM];
	int head[MAXN], en, start[MAXN];
	int S, T;
	int height[MAXN];
	bool inque[MAXN];
	int cost;
	void insert(int u, int v, int w, int c)
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
		static queue<int> q;
		memset(inque, false, sizeof(inque));
		memset(height, 63, sizeof(height));
		q.push(S);
		height[S] = 0;
		while(!q.empty())
		{
			int now = q.front();
			inque[now] = false;
			q.pop();
			for(int i = head[now]; i > 0; i = e[i].next)
				if(e[i].v && height[e[i].to] > height[now] + e[i].c)
				{
					height[e[i].to] = height[now] + e[i].c;
					if(!inque[e[i].to])
					{
						inque[e[i].to] = true;
						q.push(e[i].to);
					}
				}
		}
		return height[T] < oo;
	}
	int dfs(int p, int maxflow)
	{
		if(p == T)
			return maxflow;
		inque[p] = true;
		int allflow = maxflow;
		for(int &i = start[p]; i > 0; i = e[i].next)
			if(e[i].v && !inque[e[i].to] && height[e[i].to] == height[p] + e[i].c)
			{
				int tmp = dfs(e[i].to, e[i].v < maxflow ? e[i].v : maxflow);
				e[i].v -= tmp;
				e[i ^ 1].v += tmp;
				cost += tmp * e[i].c;
				if(!(maxflow -= tmp))
					break;
			}
		inque[p] = false;
		return allflow - maxflow;
	}
	int dinic()
	{
		int allflow = 0;
		while(spfa())
		{
			memcpy(start, head, sizeof(head));
			allflow += dfs(S, oo);
		}
		return allflow;
	}
public:
	int getmin(vector<string> field)
	{
		memset(head, -1, sizeof(head));
		en = 1;
		cost = 0;
		int n = field.size(), m = field[0].size();
		S = n * m * 3;
		T = S + 1;
		int cntodd = 0, cnteven = 0;
		for(int i = 0; i < n; i++)//build graph
			for(int j = 0; j < m; j++)
			{
				if(field[i][j] == 'w')
					continue;
				const int now = i * m + j;
				if((i ^ j) & 1)//odd point
				{
					cntodd++;
					insert(S, now, 2, 0);
					if(field[i][j] == 'C')
					{
						insert(now, now + n * m, 1, 0);//chai dian 
						insert(now, now + n * m, 1, 1);
						insert(now, now + 2 * n * m, 1, 0);
						insert(now, now + 2 * n * m, 1, 1);
					}
					else
					{
						insert(now, now + n * m, 2, 0);
						insert(now, now + 2 * n * m, 2, 0);
					}
					if(j && field[i][j - 1] != 'w')//row edge
						insert(now + n * m, now - 1 + n * m, 1, 0);
					if(j != m - 1 && field[i][j + 1] != 'w')
						insert(now + n * m, now + 1 + n * m, 1, 0);
					if(i && field[i - 1][j] != 'w')//column edge
						insert(now + 2 * n * m, now - m + 2 * n * m, 1, 0);
					if(i != n - 1 && field[i + 1][j] != 'w')
						insert(now + 2 * n * m, now + m + 2 * n * m, 1, 0);
				}
				else//even point
				{
					cnteven++;
					insert(now, T, 2, 0);
					if(field[i][j] == 'C')
					{
						insert(now + n * m, now, 1, 0);
						insert(now + n * m, now, 1, 1);
						insert(now + 2 * n * m, now, 1, 0);
						insert(now + 2 * n * m, now, 1, 1);
					}
					else
					{
						insert(now + n * m, now, 2, 0);
						insert(now + 2 * n * m, now, 2, 0);
					}
				}
			}
		if(cntodd != cnteven)//can't match
			return -1;
		if(dinic() != cntodd * 2)//can't match
			return -1;
		return cost;//answer = mincost
	}
};

