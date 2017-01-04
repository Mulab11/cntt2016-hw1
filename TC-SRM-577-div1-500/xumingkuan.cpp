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

class EllysChessboard
{
private:
	static const int MAXN = 15;
	bool a[MAXN][MAXN];//just like the board
	int f[MAXN][MAXN][MAXN][MAXN];//f[i1][i2][j1][j2]: min cost to place all the pebbles (x, y) where x is in [i1, i2] and y is in [j1, j2]
	int pos[MAXN][MAXN][MAXN][MAXN][4];//position of the most up/down/left/right pebble
	int *tmp;
	int rowsum[MAXN + 1][MAXN + 1], colsum[MAXN + 1][MAXN + 1], totsum[MAXN + 1][MAXN + 1];//1-d prefix sum and 2-d prefix sum (1-based)
public:
	int minCost(vector<string> board)
	{
		memset(a, false, sizeof(a));
		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++)
				if(board[i][j] == '#')//printf("(%d,%d)\n", i + j, i - j + 7),//for debug
					a[i + j][i - j + 7] = true;//change (x, y) to (x + y, x - y + 7), then the distance will be max(|x1-x2|, |y1-y2|)
		const int n = 14;
		for(int i1 = n; i1 >= 0; i1--)//up
		{
			tmp = rowsum[i1];
			tmp[0] = 0;
			for(int j = 1; j <= n + 1; j++)//get row sum
				tmp[j] = tmp[j - 1] + a[i1][j - 1];
			for(int i2 = i1; i2 <= n; i2++)
				for(int j1 = n; j1 >= 0; j1--)
					for(int j2 = j1; j2 <= n; j2++)
						pos[i1][i2][j1][j2][0] = (tmp[j2 + 1] - tmp[j1]) ? i1 : i1 == i2 ? i1 + 1 : pos[i1 + 1][i2][j1][j2][0];
		}
		for(int i2 = 0; i2 <= n; i2++)//down
		{
			tmp = rowsum[i2];
			for(int i1 = i2; i1 >= 0; i1--)
				for(int j1 = n; j1 >= 0; j1--)
					for(int j2 = j1; j2 <= n; j2++)
						pos[i1][i2][j1][j2][1] = (tmp[j2 + 1] - tmp[j1]) ? i2 : i1 == i2 ? i2 - 1 : pos[i1][i2 - 1][j1][j2][1];
		}
		memset(totsum, 0, sizeof(totsum));
		for(int j1 = n; j1 >= 0; j1--)//left
		{
			tmp = colsum[j1];
			tmp[0] = 0;
			for(int i = 1; i <= n + 1; i++)//get column sum and 2-d prefix sum
			{
				tmp[i] = tmp[i - 1] + a[i - 1][j1];
				totsum[i][j1 + 1] = totsum[i - 1][j1 + 1] + rowsum[i - 1][j1 + 1];
			}
			for(int j2 = j1; j2 <= n; j2++)
				for(int i1 = n; i1 >= 0; i1--)
					for(int i2 = i1; i2 <= n; i2++)
						pos[i1][i2][j1][j2][2] = (tmp[i2 + 1] - tmp[i1]) ? j1 : j1 == j2 ? j1 + 1 : pos[i1][i2][j1 + 1][j2][2];
		}
		for(int j2 = 0; j2 <= n; j2++)//right
		{
			tmp = colsum[j2];
			for(int j1 = j2; j1 >= 0; j1--)
				for(int i1 = n; i1 >= 0; i1--)
					for(int i2 = i1; i2 <= n; i2++)
						pos[i1][i2][j1][j2][3] = (tmp[i2 + 1] - tmp[i1]) ? j2 : j1 == j2 ? j2 - 1 : pos[i1][i2][j1][j2 - 1][3];
		}
		memset(f, 63, sizeof(f));
		#define update(x, y) x = min(x, y)
		for(int i1 = n; i1 >= 0; i1--)
			for(int i2 = i1; i2 <= n; i2++)
				for(int j1 = n; j1 >= 0; j1--)
					for(int j2 = j1; j2 <= n; j2++)
					{
						if(totsum[i2 + 1][j2 + 1] - totsum[i1][j2 + 1] - totsum[i2 + 1][j1] + totsum[i1][j1] <= 1)//only <= 1 point
						{
							f[i1][i2][j1][j2] = 0;
							continue;
						}
						const int now = max(pos[i1][i2][j1][j2][1] - pos[i1][i2][j1][j2][0], pos[i1][i2][j1][j2][3] - pos[i1][i2][j1][j2][2]);
						update(f[i1][i2][j1][j2], f[i1 + 1][i2][j1][j2] + (rowsum[i1][j2 + 1] - rowsum[i1][j1]) * now);
						update(f[i1][i2][j1][j2], f[i1][i2 - 1][j1][j2] + (rowsum[i2][j2 + 1] - rowsum[i2][j1]) * now);
						update(f[i1][i2][j1][j2], f[i1][i2][j1 + 1][j2] + (colsum[j1][i2 + 1] - colsum[j1][i1]) * now);
						update(f[i1][i2][j1][j2], f[i1][i2][j1][j2 - 1] + (colsum[j2][i2 + 1] - colsum[j2][i1]) * now);
						/*
						const int dist[4] = {pos[i1][i2][j1][j2][1] - i1, i2 - pos[i1][i2][j1][j2][0], pos[i1][i2][j1][j2][3] - j1, j2 - pos[i1][i2][j1][j2][2]};//the cost to place pebbles at up/down/left/right
						if(i1 != i2 && pos[i1][i2][j1][j2][2] == pos[i1 + 1][i2][j1][j2][2] && pos[i1][i2][j1][j2][3] == pos[i1 + 1][i2][j1][j2][3])//up: row i1 (didn't update 'pos' left or right)
							update(f[i1][i2][j1][j2], f[i1 + 1][i2][j1][j2] + (rowsum[i1][j2 + 1] - rowsum[i1][j1]) * max(dist[0], max(dist[2], dist[3])));
						if(i1 != i2 && pos[i1][i2][j1][j2][2] == pos[i1][i2 - 1][j1][j2][2] && pos[i1][i2][j1][j2][3] == pos[i1][i2 - 1][j1][j2][3])//down: row i2 (didn't update 'pos' left or right)
							update(f[i1][i2][j1][j2], f[i1][i2 - 1][j1][j2] + (rowsum[i2][j2 + 1] - rowsum[i2][j1]) * max(dist[1], max(dist[2], dist[3])));
						if(j1 != j2 && pos[i1][i2][j1][j2][0] == pos[i1][i2][j1 + 1][j2][0] && pos[i1][i2][j1][j2][1] == pos[i1][i2][j1 + 1][j2][1])//left: column j1 (didn't update 'pos' up or down)
							update(f[i1][i2][j1][j2], f[i1][i2][j1 + 1][j2] + (colsum[j1][i2 + 1] - colsum[j1][i1]) * max(dist[2], max(dist[0], dist[1])));
						if(j1 != j2 && pos[i1][i2][j1][j2][0] == pos[i1][i2][j1][j2 - 1][0] && pos[i1][i2][j1][j2][1] == pos[i1][i2][j1][j2 - 1][1])//right: column j2 (didn't update 'pos' up or down)
							update(f[i1][i2][j1][j2], f[i1][i2][j1][j2 - 1] + (colsum[j2][i2 + 1] - colsum[j2][i1]) * max(dist[3], max(dist[0], dist[1])));
						if(i1 != i2 && j1 != j2)//update 'pos' in 2 directions
						{
							if(a[i1][j1] && !(rowsum[i1][j2 + 1] - rowsum[i1][j1 + 1]) && !(colsum[j1][i2 + 1] - colsum[j1][i1 + 1]))//up left
								update(f[i1][i2][j1][j2], f[i1 + 1][i2][j1 + 1][j2] + max(dist[0], dist[2]));
							if(a[i1][j2] && !(rowsum[i1][j2] - rowsum[i1][j1]) && !(colsum[j2][i2 + 1] - colsum[j2][i1 + 1]))//up right
								update(f[i1][i2][j1][j2], f[i1 + 1][i2][j1][j2 - 1] + max(dist[0], dist[3]));
							if(a[i2][j1] && !(rowsum[i2][j2 + 1] - rowsum[i2][j1 + 1]) && !(colsum[j1][i2] - colsum[j1][i1]))//down left
								update(f[i1][i2][j1][j2], f[i1][i2 - 1][j1 + 1][j2] + max(dist[1], dist[2]));
							if(a[i2][j2] && !(rowsum[i2][j2] - rowsum[i2][j1]) && !(colsum[j2][i2] - colsum[j2][i1]))//down right
								update(f[i1][i2][j1][j2], f[i1][i2 - 1][j1][j2 - 1] + max(dist[1], dist[3]));
						}
						//if(f[i1][i2][j1][j2] && f[i1][i2][j1][j2] != f[i1 + 1][i2][j1][j2] && f[i1][i2][j1][j2] != f[i1][i2 - 1][j1][j2] && f[i1][i2][j1][j2] != f[i1][i2][j1 + 1][j2] && f[i1][i2][j1][j2] != f[i1][i2][j1][j2 - 1])//for debug
						//	printf("f[%d,%d][%d,%d] = %d\n", i1, i2, j1, j2, f[i1][i2][j1][j2]);
						*/
					}
		return f[0][n][0][n];
	}
};

