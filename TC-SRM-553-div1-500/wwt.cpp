/*
dp。注意到两种颜色从上往下肯定是把每一条线分成两边，并且一个长度递减一个长度递增。那么设状态f[x][y][sta]表示做到第x行，一个的长度是y，
两个的状态为sta(递减，递增，未出现)。因为可能可以交换两种颜色，所以要另外设ok_left和ok_right表示某种颜色是否能放在左（右）边，
把一种颜色占领整行时不区分左右这种情况判好就行了。
*/
#include <bits/stdc++.h>

using namespace std;

const int mo = int(1e9) + 7;

class TwoConvexShapes
{
public:
	int f[55][55][3][2][2],le[55][55],ri[55][55],n,m;

	int dfs(int x,int y,int sta,bool lef,bool rig)
	{
		if (!(lef || rig)) return 0;
		if (x == n)
		{
			if (y == m && sta == 2) //avoid double caculation
				return 0;
			return lef + rig;
		}
		int &ret = f[x][y][sta][lef][rig];
		if (~ret) return ret;
		ret = 0;
		for(int cl = 0;cl <= m;cl ++)
		{
			if (sta == 1 && cl < y || sta == 0 && cl > y) continue;
			if (y == m && cl == 0) continue;//avoid double caculation 
			int nsta = sta;
			if (cl < y) nsta = 0; else if (cl > y) nsta = 1;
			if (!x) nsta = 2;
			ret = (ret + dfs(x + 1,cl,nsta,lef && le[x][cl],rig && ri[x][cl])) % mo;
		}
		return ret;
	}

	int countWays(vector <string> grid)
	{
		n = grid.size(),m = grid[0].length();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j <= m;j ++)
			{
				le[i][j] = 1;
				for(int k = 0;k < j;k ++)
					if (grid[i][k] == 'W') le[i][j] = 0; //左边不能放b
				for(int k = j;k < m;k ++)
					if (grid[i][k] == 'B') le[i][j] = 0;
				ri[i][j] = 1;
				for(int k = 0;k < j;k ++)
					if (grid[i][k] == 'B') ri[i][j] = 0;//右边不能放b
				for(int k = j;k < m;k ++)
					if (grid[i][k] == 'W') ri[i][j] = 0;
			}
		memset(f,255,sizeof f);
		return dfs(0,0,2,1,1);
	}
};
