//随便模拟一下可以发现n=max(move[1],move[3]),m = max(move[0],move[2]),x = n - move[1],y = m - move[0];
///然后模拟一遍看一下是否合法即可。
#include <bits/stdc++.h>

using namespace std;

const int xy[4][2] = {{1,0},{0,-1},{-1,0},{0,1}};

class RotatingBot
{
public:
	int minArea(vector<int> moves)
	{
		int fs = moves.size();
		moves.resize(4,0);
		int m = max(moves[0],moves[2]),n = max(moves[1],moves[3]),y = m - moves[0],x = n - moves[1];
		static bool cover[55][55];
		memset(cover,0,sizeof cover);
		int dir = 3;
		for(int i = 0;i < fs;i ++)
		{
			int co = 0;
			for(;;co ++) //模拟走法
			{
				cover[x][y] = 1;
				int nx = x + xy[dir][0],ny = y + xy[dir][1];
				if (!(nx >= 0 && ny >= 0 && nx <= n && ny <= m && !cover[nx][ny])) break;
				x = nx,y = ny;
			}
			if (co < moves[i] || (i != fs - 1 && co > moves[i])) return -1;
			dir = (dir + 1) % 4;
		}
		return (n + 1) * (m + 1);
	}
};
