#include <bits/stdc++.h>

using namespace std;

const int maxn = 85;

class EllysChessboard
{
public:
	int a[maxn][2];
	int f[16][16][16][16],n;

	bool in(int p,int lx,int rx,int ly,int ry)
	{
		return a[p][0] >= lx && a[p][0] <= rx && a[p][1] >= ly && a[p][1] <= ry;
	}

	int get_cost(int p,int lx,int rx,int ly,int ry)
	{
		return max(max(abs(a[p][0] - lx),abs(a[p][0] - rx)),max(abs(a[p][1] - ly),abs(a[p][1] - ry)));
	}

	int calc(int lx,int rx,int ly,int ry) //assume that we have put every point in [lx,rx]+[ly,ry],what's the minimum cost to put others.
	{
		int &tmp = f[lx][rx][ly + 8][ry + 8];
		if (~tmp) return tmp;
		tmp = (1 << 30);
		bool allin = 1;
		for(int i = 0;i < n;i ++)
			if (!in(i,lx,rx,ly,ry)) allin = 0;
		if (allin) return tmp = 0;
		for(int i = 0;i < n;i ++) //the next point to put
			if (!in(i,lx,rx,ly,ry))
			{
				int c = get_cost(i,lx,rx,ly,ry);
				int nix = min(lx,a[i][0]),nxx = max(rx,a[i][0]);
				int niy = min(ly,a[i][1]),nxy = max(ry,a[i][1]);
				for(int j = 0;j < n;j ++)
					if (i != j && in(j,nix,nxx,niy,nxy) && !in(j,lx,rx,ly,ry)) //to put the point in the new rectangle
						c += get_cost(j,nix,nxx,niy,nxy);
				tmp = min(tmp,c + calc(nix,nxx,niy,nxy));
			}
		return tmp;
	}

	int minCost(vector<string> board)
	{
		memset(f,255,sizeof f);
		for(int i = 0;i < board.size();i ++)
			for(int j = 0;j < board[i].length();j ++)
				if (board[i][j] == '#')
					a[n ++][0] = i + j,a[n - 1][1] = i - j;// rotate 45 degrees
		//now |x-x1|+|y-y1|=max(|x'-x1'|,|y'-y1'|)
		int ans = (1 << 30);
		if (!n) ans = 0;
		for(int i = 0;i < n;i ++)
		{ 
			ans = min(ans,calc(a[i][0],a[i][0],a[i][1],a[i][1])); //enumerate the first point
		}
		return ans;
	}
};
