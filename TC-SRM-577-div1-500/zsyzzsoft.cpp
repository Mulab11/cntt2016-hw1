#include <algorithm>
#include <memory.h>
using namespace std;
bool map[16][16];
int f[16][16][16][16];
class EllysChessboard
{
public:
	int Sum(int l, int b, int r, int t, int i, int j, int u, int v)
	{
		int sum = 0;
		for(int x = l; x <= r; x++)
		{
			for(int y = b; y <= t; y++)
			{
				if(map[x][y]) //放棋子的代价 
					sum += max(max(abs(x - i), abs(x - u)), max(abs(y - j), abs(y - v)));
			}
		}
		return sum;
	}
	int Dfs(int i, int j, int u, int v) //一定放完一个矩形里的所有棋子 
	{
		if(f[i][j][u][v] >= 0)
			return f[i][j][u][v];
		int ans = 2147483647;
		if(i < u)
			ans = min(ans, min(Dfs(i + 1, j, u, v) + Sum(i, j, i, v, i, j, u, v), Dfs(i, j, u - 1, v) + Sum(u, j, u, v, i, j, u, v)));
		if(j < v)
			ans = min(ans, min(Dfs(i, j + 1, u, v) + Sum(i, j, u, j, i, j, u, v), Dfs(i, j, u, v - 1) + Sum(i, v, u, v, i, j, u, v)));
		return f[i][j][u][v] = ans;
	}
	int minCost(vector<string> board)
	{
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				if(board[i][j] == '#')
					map[i + j][i - j + 8] = true; //坐标变换 
			}
		}
		memset(f, -1, sizeof(f));
		for(int i = 0; i < 16; i++)
		{
			for(int j = 0; j < 16; j++)
				f[i][j][i][j] = 0;
		}
		return Dfs(0, 0, 15, 15);
	}
};