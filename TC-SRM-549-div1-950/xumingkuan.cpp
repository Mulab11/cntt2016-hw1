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
using namespace std;
const int MAXN = 70, MAXM = 500, oo = 1010101010;
namespace Dinic
{
class Edge
{
	public:
		int to, v, next;
};
Edge e[MAXM];
int head[MAXN], en = 1, start[MAXN], height[MAXN], S, T;
queue <int> q;
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
	memset(height, 63, sizeof(height));
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
}

class CosmicBlocks
{
	private:
	int n, a[8], height[8], mnw, mxw;//a[i] = blockTypes[i]
	int f[MAXN];//f[S]: status S, removing ways
	bool e[8][8];//edge, up -> down
	int ans;
	bool checkvalid()
	{
		int tot = 0;
		int indeg[8], outdeg[8];
		memset(indeg, 0, sizeof(indeg));
		memset(outdeg, 0, sizeof(outdeg));
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if(e[i][j])
					indeg[j]++, outdeg[i]++;
		for(int i = 0; i < n; i++)
			if(indeg[i] > a[i] || outdeg[i] > a[i])//at least one block per edge
				return false;
		memset(Dinic::head, -1, sizeof(Dinic::head));
		Dinic::en = 1;
		Dinic::S = 2 * n;
		Dinic::T = 2 * n + 1;
		for(int i = 0; i < n; i++)
		{
			Dinic::insert(n + i, Dinic::T, a[i] - indeg[i]);
			if(height[i] == 0)
				continue;
			Dinic::insert(Dinic::S, i, a[i] - outdeg[i]);
			tot += a[i] - outdeg[i];
			for(int j = 0; j < n; j++)
				if(e[i][j])
					Dinic::insert(i, n + j, oo);
		}
		if(Dinic::dinic() != tot)//can't arrange
			return false;
		//now we can throw a[i] into the dustbin, and care only about edges and ways.
		memset(f, 0, sizeof(f));
		f[0] = 1;//empty, 1 way
		for(int i = 1; i < (1 << n); i++)
		{
			for(int j = 0; j < n; j++)//try to remove j
			{
				if(!((i >> j) & 1))//status i doesn't contain j
					continue;
				bool flag = true;
				for(int k = 0; k < n; k++)
					if(e[k][j] && ((i >> k) & 1))//i contains k && k is on j, illegal
					{
						flag = false;
						break;
					}
				if(flag)
					f[i] += f[i ^ (1 << j)];
			}
		}
		return (f[(1 << n) - 1] >= mnw && f[(1 << n) - 1] <= mxw);//whether the number of ways satisfy the condition
	}
	void search(int h, int p, const vector <int> &last)//h: height, p: place, last: colors at height - 1
	{
		//printf("search %d %d\n", h, p);
		if(p == n)
		{
			vector <int> now;
			bool over = true;
			int tmp1 = 0, tmp2 = 0;
			for(int i = 0; i < n; i++)
			{
				if(height[i] == -1)
					over = false;
				if(height[i] == h)
				{
					now.push_back(i);
					tmp2 += a[i];
				}
			}
			if(now.empty())//no color at this height, illegal
				return;
			for(int i = 0; i < last.size(); i++)
				tmp1 += a[last[i]];
			if(h > 0 && tmp1 < tmp2)//up > down, illegal
				return;
			if(over)
			{
				if(checkvalid())
					ans++;
			}
			else
				search(h + 1, 0, now);
			return;
		}
		search(h, p + 1, last);
		if(height[p] != -1)//p is already put at some lower height
			return;
		height[p] = h;
		if(!h)
			search(h, p + 1, last);
		else
		{
			const int tmp = last.size();
			for(int i = 0; i < (1 << tmp); i++)
			{
				for(int j = 0; j < tmp; j++)
					e[p][last[j]] = (i >> j) & 1;
				search(h, p + 1, last);
			}
		}
		memset(e[p], false, sizeof(e[p]));
		height[p] = -1;
	}
	public:
	int getNumOrders(vector<int> blockTypes, int minWays, int maxWays)
	{
		n = blockTypes.size();
		mnw = minWays;
		mxw = maxWays;
		ans = 0;
		for(int i = 0; i < n; i++)
			a[i] = blockTypes[i];
		memset(height, -1, sizeof(height));
		memset(e, false, sizeof(e));
		search(0, 0, vector <int> ());
		return ans;
	}
};

