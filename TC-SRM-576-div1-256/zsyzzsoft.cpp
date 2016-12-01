#include <algorithm>
using namespace std;
int st[2500];
class ArcadeManao
{
public:
	int n, m;
	int Find(int x)
	{
		return st[x] < 0 ? x : st[x] = Find(st[x]);
	}
	int Find(int u, int v)
	{
		return Find(u * m + v);
	}
	void Union(int i, int j, int u, int v)
	{
		if(Find(i, j) != Find(u, v))
			st[Find(i, j)] = Find(u, v);
	}
	int shortestLadder(vector<string> level, int x, int y)
	{
		n = level.size(), m = level[0].size(), x--, y--;
		for(int i = 0; i < n * m; i++)
			st[i] = -1;
		for(int i = 0; i < n; i++)
		{
			for(int j = 1; j < m; j++)
			{
				if(level[i][j] == 'X' && level[i][j - 1] == 'X')
					Union(i, j, i, j - 1); //横向连接 
			}
		}
		for(int l = 1; l <= n; l++) //递增梯子长度 
		{
			if(Find(x, y) == Find(n - 1, 0))
				return l - 1;
			for(int i = 0; i + l < n; i++)
			{
				for(int j = 0; j < m; j++)
				{
					if(level[i][j] == 'X' && level[i + l][j] == 'X')
						Union(i, j, i + l, j); //纵向连接 
				}
			}
		}
		return -1;
	}
};