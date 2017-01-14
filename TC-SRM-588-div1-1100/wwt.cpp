#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;
const int xy[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

int dis[2][maxn][maxn];//(x,y)与A/B的距离
int n,m;

class GameInDarknessDiv1
{
public:
	vector<string> f;

	bool legal(int x,int y)
	{
		return (x >= 0 && y >= 0 && x < n && y < m && f[x][y] != '#');
	}

	void get_dis(int type,int x,int y,int px,int py,int d)
	{
		if (!legal(x,y)) return;
		dis[type][x][y] = d;
		for(int i = 0;i < 4;i ++)
			if (x + xy[i][0] == px && y + xy[i][1] == py) continue; else //cannot walk back
				get_dis(type,x + xy[i][0],y + xy[i][1],x,y,d + 1);
	}

	int max_dis(int x,int y,int px,int py) //get the maximum distance from one point in (x,y)'s subtree to (px,py)
	{
		if (!legal(x,y)) return 0;
		int tmp = 0;
		for(int i = 0;i < 4;i ++)
			if (x + xy[i][0] == px && y + xy[i][1] == py) continue; else
				tmp = max(tmp,max_dis(x + xy[i][0],y + xy[i][1],x,y));
		return tmp + 1;
	}

	string check(vector<string> field)
	{
		f = field;
		n = field.size(),m = field[0].length();
		int x[2],y[2];
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (field[i][j] == 'A') x[0] = i,y[0] = j; else
					if (field[i][j] == 'B') x[1] = i,y[1] = j;
		for(int i = 0;i < 2;i ++) get_dis(i,x[i],y[i],-1,-1,0);
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (legal(i,j) && dis[0][i][j] - dis[1][i][j] >= 2) 
				{
					int cnt = 0;
					for(int d = 0;d < 4;d ++)
						if (max_dis(i + xy[d][0],j + xy[d][1],i,j) > 2) ++ cnt;
					if (cnt >= 3) return "Bob wins"; //a possible crossing is found,Bob will win.
				}
		return "Alice wins";
	}
};
