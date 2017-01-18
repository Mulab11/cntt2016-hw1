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
const int MAXN = 2525, MAXM = 30303, oo = 1010101010;
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
class FoxAndGo3
{
private:
	int n, m;//n * m board
	int number[55][55];//number of connected block of white pieces
	int sz[2525];//size of connected block of white pieces; -1 if it's '.'
	queue<pair<int, int> > q;
	bool in(int x, int y)
	{
		return x >= 0 && x < n && y >= 0 && y < m;
	}
public:
	int maxEmptyCells(vector<string> board)
	{
		n = board.size(), m = board[0].size();
		memset(number, 0, sizeof(number));
		sz[0] = 0;
		int cnt = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				if(!number[i][j] && board[i][j] == 'o')
				{
					q.push(make_pair(i, j));
					sz[number[i][j] = ++cnt] = 1;
					while(!q.empty())//bfs
					{
						int nowx = q.front().first, nowy = q.front().second;
						q.pop();
						#define check(x, y) if(in((x), (y)) && !number[x][y] && board[x][y] == 'o') sz[number[x][y] = cnt]++, q.push(make_pair(x, y))
						check(nowx - 1, nowy);
						check(nowx + 1, nowy);
						check(nowx, nowy - 1);
						check(nowx, nowy + 1);
						#undef check
					}
				}
				else if(board[i][j] == '.')
					sz[number[i][j] = ++cnt] = -1;
		S = cnt + 1;
		T = S + 1;
		clearedge();
		int ans = 0;
		for(int i = 1; i <= cnt; i++)//build graph
			if(sz[i] == -1)
				insert(S, i, 1), ans++;
			else
				insert(i, T, sz[i]), ans += sz[i];
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				if(sz[number[i][j]] == -1)
				{
					#define check(x, y) if(in((x), (y)) && sz[number[x][y]] > 0) insert(number[i][j], number[x][y], oo)
					check(i - 1, j);
					check(i + 1, j);
					check(i, j - 1);
					check(i, j + 1);
					#undef check
				}
		return ans - dinic();//min cut
	}
};

