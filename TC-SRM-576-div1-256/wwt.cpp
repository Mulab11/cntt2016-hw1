#include <bits/stdc++.h>

using namespace std;

const int xy[2][2] = {{0,1},{0,-1}};

class ArcadeManao
{
public:
	vector<string> a;
	int n,m,tx,ty;

	bool legal(int x,int y)
	{
		return x >= 0 && y >= 0 && x < n && y < m && a[x][y] == 'X';
	}

	bool test(int len)
	{
		static bool wal[55][55];
		memset(wal,0,sizeof wal);
		static int que[55 * 55][2];
		que[1][0] = n - 1,que[1][1] = 0;
		wal[n - 1][0] = 1;
		for(int fi = 1,en = 1;fi <= en;fi ++)
		{
			int x = que[fi][0],y = que[fi][1];
			for(int i = 0;i < 2;i ++) //walk horizontally
			{
				int nx = x + xy[i][0],ny = y + xy[i][1];
				if (legal(nx,ny) && !wal[nx][ny]) wal[nx][ny] = 1,que[++ en][0] = nx,que[en][1] = ny; 
			}
			for(int nx = 0;nx < n;nx ++) //use the ladder
				if (abs(nx - x) <= len && legal(nx,y))
					if (!wal[nx][y]) wal[nx][y] = 1,que[++ en][0] = nx,que[en][1] = y;
		}
		return wal[tx - 1][ty - 1];
	}

	int shortestLadder(vector <string> level, int coinRow, int coinColumn)
	{
		a = level;
		n = level.size(),m = level[0].length();
		tx = coinRow,ty = coinColumn;
		int l = 0,r = 50,tmp;
		for(int mid;l <= r;) //binary search
		{
			mid = l + r >> 1;
			if (test(mid)) tmp = mid,r = mid - 1; else l = mid + 1;
		}
		return tmp;
	}
};
