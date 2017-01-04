#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
class Edge
{
public:
	int u, v, next;
};
class ArcadeManao
{
private:
	int fa[2525];
	int getanc(int x)
	{
		return fa[x] == x ? x : fa[x] = getanc(fa[x]);
	}
	Edge e[2525];
	int head[55], en;
	void insert(int from, int u, int v)//adjacency list
	{
		e[++en].u = u;
		e[en].v = v;
		e[en].next = head[from];
		head[from] = en;
	}
public:
	int shortestLadder(vector<string> level, int coinRow, int coinColumn)//total time complexity: O(n*m*(disjoint-set))
	{
		int n = level.size(), m = level[0].size();
		int coin = (coinRow - 1) * m + (coinColumn - 1), start = n * m - 1;
		for(int i = 0; i < n * m; i++)
			fa[i] = i;
		for(int i = 0; i < n; i++)//go without ladder
			for(int j = 0; j < m - 1; j++)
				if(level[i][j] == 'X' && level[i][j + 1] == 'X')
					fa[getanc(i * m + j)] = getanc(i * m + j + 1);
		if(getanc(start) == getanc(coin))
			return 0;
		memset(head, -1, sizeof(head));
		en = 0;
		for(int j = 0; j < m; j++)
		{
			int last = n - 1;
			for(int i = n - 2; i >= 0; i--)
				if(level[i][j] == 'X')
				{
					insert(last - i, i * m + j, last * m + j);
					last = i;
				}
		}
		for(int i = 1; i < n; i++)//enumerate the length of ladder
		{
			for(int j = head[i]; j > 0; j = e[j].next)
				fa[getanc(e[j].u)] = getanc(e[j].v);
			if(getanc(start) == getanc(coin))
				return i;
		}
		return -1;//error
	}
};

