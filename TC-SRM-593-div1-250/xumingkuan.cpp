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

class HexagonalBoard
{
private:
	int n, m, ans;
	vector<string> a;//n * m board
	bool in(int x, int y)
	{
		return x >= 0 && x < n && y >= 0 && y < m;
	}
	void bfs(int x, int y)
	{
		static queue<pair<int, int> > q;
		q.push(make_pair(x, y));
		if(ans < 1)//at least 1 color
			ans = 1;
		a[x][y] = 'R';//color it red
		while(!q.empty())
		{
			x = q.front().first, y = q.front().second;
			q.pop();
			#define check(u, v) if(in((u), (v)))\
			{\
				if(a[u][v] == 'X')\
				{\
					q.push(make_pair((u), (v)));\
					a[u][v] = a[x][y] ^ 1;\
					if(ans < 2)/*adjacent 'X': at least 2 colors*/\
						ans = 2;\
				}\
				else if(a[u][v] == a[x][y])\
					ans = 3;/*we can color everything with 3 colors*/\
			}
			check(x, y + 1)
			check(x + 1, y)
			check(x + 1, y - 1)
			check(x, y - 1)
			check(x - 1, y)
			check(x - 1, y + 1)
		}
	}
public:
	int minColors(vector<string> board)
	{
		a = board;
		n = a.size(), m = a[0].size();
		ans = 0;
		for(int i = 0; i < n && ans < 3; i++)
			for(int j = 0; j < m && ans < 3; j++)
				if(a[i][j] == 'X')
					bfs(i, j);
		return ans;
	}
};

