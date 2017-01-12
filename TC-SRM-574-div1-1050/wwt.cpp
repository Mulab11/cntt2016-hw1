#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;
const int xy[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
 
class Tunnels
{
public:
	vector<string> fr;
	int full[maxn];//row i is filled with 'X'
	bool lup[maxn],rup[maxn],ldow[maxn],rdow[maxn]; //whether row i can link upward,the same to others
	int n,m;
	int f[maxn][maxn][maxn];//row,number of available left bracket,the same to right
	int bel[maxn][maxn],cnt;//the component that (x,y) belongs to.
	int deg[maxn][maxn]; //how many blocks that is connected to (x,y)

	bool legal(int x,int y) 
	{
		return !(x < 0 || y < 0 || x >= n || y >= m || fr[x][y] != 'X');
	}

	void dfs(int x,int y)
	{
		if (!legal(x,y) || bel[x][y] != -1) return;
		bel[x][y] = cnt;
		for(int i = 0;i < 4;i ++)
			dfs(x + xy[i][0],y + xy[i][1]);
	}

	int dp()
	{
		memset(f,200,sizeof f);
		f[n][0][0] = 0;
		for(int i = n - 1;i >= 0;i --)
			for(int lc = 0;lc <= i;lc ++)
				for(int rc = 0;rc <= i;rc ++)
					for(int a = -1;a <= 1;a ++) //whether to connect upward or create a new left bracket
						for(int b = -1;b <= 1;b ++) //the same to the right
						{
							if (a == -1 && !lup[i] || a == 1 && !ldow[i] 
								|| b == -1 && !rup[i] || b == 1 && !rdow[i]) continue;
							if (full[i] && (a == b) && a) continue;
							int nl = lc + a,nr = rc + b;
							if (nl >= 0 && nr >= 0)
								f[i][lc][rc] = max(f[i + 1][nl][nr] + (a == -1) + (b == -1),f[i][lc][rc]);
						}
		return f[0][0][0];
	}

	int minimumTunnels(vector<string> frame)
	{
		fr = frame;
		n = frame.size(),m = frame[0].length();
		memset(bel,255,sizeof bel);
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (bel[i][j] == -1 && frame[i][j] == 'X') dfs(i,j),++ cnt;
		if (m == 1) //we have to specify this situation.
		{
			if (cnt) return 1;
			return 0;
		}
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
			{
				deg[i][j] = 0;
				for(int k = 0;k < 4;k ++)
					if (legal(i + xy[k][0],j + xy[k][1])) ++ deg[i][j];
			}
		static int minr[maxn * maxn],maxr[maxn * maxn]; //the minimum row which belongs to component i,vice versa
		for(int i = 0;i < cnt;i ++) minr[i] = (1 << 30);
		for(int i = 0;i < n;i ++) 
		{
			lup[i] = rup[i] = ldow[i] = rdow[i] = full[i] = 0;
			for(int j = 0;j < m;j ++)
				if (frame[i][j] == 'X') 
					minr[bel[i][j]] = min(minr[bel[i][j]],i),maxr[bel[i][j]] = max(maxr[bel[i][j]],i);
		}
		for(int i = 0;i < n;i ++)
		{
			if (frame[i][0] == 'X' && deg[i][0] <= 1 && i == minr[bel[i][0]]) //only when deg[i][0] <= 1,then row i can connect upward 
				lup[i] = 1;
			if (frame[i][0] == 'X' && deg[i][0] <= 1 && i == maxr[bel[i][0]]) //only when deg[i][0] <= 1,then row i can connect downward 
				ldow[i] = 1;
		}
		//do the same thing to right
		for(int i = 0;i < n;i ++)
		{
			if (frame[i][m - 1] == 'X' && deg[i][m - 1] <= 1 && i == minr[bel[i][m - 1]])
				rup[i] = 1;
			if (frame[i][m - 1] == 'X' && deg[i][m - 1] <= 1 && i == maxr[bel[i][m - 1]])
				rdow[i] = 1;
		}
		//be cautious to x..
		//		     x..,we cannot let the upper one connect upward which another connects downward,except row 0
		for(int i = 1;i < n - 1;i ++)
			if (frame[i][0] == 'X' && i == minr[bel[i][0]] && bel[i][0] == bel[i + 1][0] && maxr[bel[i][0]] == i + 1)
				ldow[i + 1] &= !(lup[i]);
		for(int i = 1;i < n - 1;i ++)
			if (frame[i][m - 1] == 'X' && i == minr[bel[i][m - 1]] && 
					bel[i][m - 1] == bel[i + 1][m - 1] && maxr[bel[i][m - 1]] == i + 1)
				rdow[i + 1] &= !(rup[i]);
		for(int i = 0;i < n;i ++)
			if (bel[i][0] == bel[i][m - 1] && bel[i][0] != -1) full[i] = 1;
		//consider .......
		//         xxxx...
		//         ....... you cannot connect downward
		for(int i = 1;i < n;i ++)
		{
			int left = bel[i][0],right = bel[i][m - 1];
			if (left != right)
			{
				if (left != -1 && minr[left] == maxr[left]) ldow[i] = 0;
				if (right != -1 && minr[right] == maxr[right])  rdow[i] = 0;
			}
		}
		return cnt - dp(); //ans = the number of component - the components that we can match
	}
};
