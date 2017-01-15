#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

vector<int> lk[maxn * maxn];
int ord[maxn][maxn],col[maxn * maxn],ap[2],cnt;

class HexagonalBoard
{
public:

	bool dfs(int now,int c)
	{
		ap[c] ++;
		col[now] = c;
		for(auto p : lk[now])
		{
			if (col[p] == -1 && !dfs(p,c ^ 1)) return 0;
			if ((col[p] ^ 1) != c) return 0;
		}
		return 1;
	}

	int minColors(vector<string> board)
	{
		int n = board.size(),m = board[0].length();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (board[i][j] == 'X') ord[i][j] = ++ cnt;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (ord[i][j])
					for(int x = -1;x <= 1;x ++)
						for(int y = -1;y <= 1;y ++)
						{
							if (x == 1 && y == 1) continue;
							if (x == -1 && y == -1) continue;
							if (x || y)
								if (i + x >= 0 && j + y >= 0 && i + x < n && j + y < m && ord[i + x][j + y])
									lk[ord[i][j]].push_back(ord[i + x][j + y]);
						}
		memset(col,255,sizeof col);memset(ap,0,sizeof ap);
		for(int i = 1;i <= cnt;i ++)
			if (col[i] == -1) 
				if (!dfs(i,0)) return 3;
		if (!ap[0]) return 0;
		if (!ap[1]) return 1;
		return 2;
	}
};
