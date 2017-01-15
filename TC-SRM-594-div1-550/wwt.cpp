#include <bits/stdc++.h>

using namespace std;

const int maxn = 2505;
const int xy[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

int ord[55][55],vis[maxn],lx[maxn],Ref[maxn][2],cnt,n,m;

class FoxAndGo3
{
public:
	int dfs(int now)
	{
		int x = Ref[now][0],y = Ref[now][1];
		for(int i = 0;i < 4;i ++)
		{
			int nx = x + xy[i][0],ny = y + xy[i][1];
			if (nx >= 0 && ny >= 0 && nx < n && ny < m && ord[nx][ny]) //找到相邻的空点
			{
				int p = ord[nx][ny];
				if (vis[p]) continue;
				vis[p] = 1;
				if (!lx[p] || dfs(lx[p])) return lx[p] = now,1;
			}
		}
		return 0;
	}

	int maxEmptyCells(vector<string> board)
	{
		//一个白点能变成空点当且仅当其所有相邻空格都变成黑点
		//假如一开始所有白点都能变成空点
		//S->白点流量为1，白点->相邻空格流量为1，空格->T流量为1，答案-最小割
		//二分图，最大匹配即可。
		n = board.size(),m = board[0].length();
		int ans = 0;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (board[i][j] != 'x') ord[i][j] = ++ cnt,Ref[cnt][0] = i,Ref[cnt][1] = j,ans ++;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (board[i][j] == 'o')
				{
					memset(vis,0,sizeof vis);
					ans -= dfs(ord[i][j]);
				}					
		return ans;	
	}
};
