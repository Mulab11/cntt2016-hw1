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
const int oo = 101010;
class YetAnotherBoardGame
{
private:
	int n, m;
	bool a[15][15];//board
	int col[15][2];//column type
	inline bool in(int x, int y)
	{
		return x >= 0 && x < n && y >= 0 && y < m;
	}
	void move(int x, int y, bool type, bool add)
	{
		if(type)
			a[x][y] = !a[x][y];
		if(in(x - 1, y))
			a[x - 1][y] = !a[x - 1][y];
		if(in(x + 1, y))
			a[x + 1][y] = !a[x + 1][y];
		if(in(x, y - 1))
			a[x][y - 1] = !a[x][y - 1];
		if(in(x, y + 1))
			a[x][y + 1] = !a[x][y + 1];
		if(add)
			col[y][type]++;
		else
			col[y][type]--;
	}
	int searchrow(int p)
	{
		vector<int> now;//white cells in line p-1
		for(int i = 0; i < m; i++)
			if(a[p - 1][i])
				now.push_back(i);
		if(p == n)
			return now.empty() ? 0 : oo;//there shouldn't be any white cells
		int ret = oo;
		for(int tp = 0; tp <= 1; tp++)//row type
		{
			bool ok = true;
			for(int i = 0; i < now.size(); i++)
				if(col[now[i]][!tp])//different type in the same column
				{
					ok = false;
					break;
				}
			if(!ok)
				continue;
			for(int i = 0; i < now.size(); i++)
				move(p, now[i], tp, true);
			ret = min(ret, searchrow(p + 1) + (int)now.size());//(now.size()) moves
			for(int i = 0; i < now.size(); i++)
				move(p, now[i], tp, false);
		}
		return ret;
	}
	int searchcol(int p, int row0type)
	{
		if(p == m)
			return searchrow(1);
		int ret = searchcol(p + 1, row0type);//no moves
		if(row0type & 1)//type 1 move
		{
			move(0, p, false, true);
			ret = min(ret, searchcol(p + 1, 1) + 1);
			move(0, p, false, false);
		}
		if(row0type & 2)//type 2 move
		{
			move(0, p, true, true);
			ret = min(ret, searchcol(p + 1, 2) + 1);
			move(0, p, true, false);
		}
		return ret;
	}
public:
	int minimumMoves(vector<string> board)
	{
		n = board.size();
		m = board[0].size();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				a[i][j] = (board[i][j] == 'W');
		memset(col, 0, sizeof(col));
		int ans = searchcol(0, 3);
		return ans >= oo ? -1 : ans;
	}
};

