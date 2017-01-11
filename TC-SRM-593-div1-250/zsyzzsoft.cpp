#include <algorithm>
using namespace std;
const int dx[6] = {-1, 1, 0, 0, -1, 1}, dy[6] = {0, 0, -1, 1, 1, -1};
int n, sum, col[50][50];
bool flag, both, map[50][50];
class HexagonalBoard
{
public:
	void Dfs(int i, int j)
	{
		if(col[i][j])
			both = true;
		for(int k = 0; k < 6; k++)
		{
			int ni = i + dx[k], nj = j + dy[k];
			if(ni < 0 || nj < 0 || ni >= n || nj >= n || !map[ni][nj])
				continue;
			if(col[ni][nj] < 0)
				col[ni][nj] = !col[i][j], Dfs(ni, nj);
			else if(col[ni][nj] == col[i][j])
				flag = true;
		}
	}
	int minColors(vector<string> board)
	{
		n = board.size();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				sum += map[i][j] = board[i][j] == 'X', col[i][j] = -1;
		}
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(map[i][j] && col[i][j] < 0)
					col[i][j] = 0, Dfs(i, j);
			}
		}
		if(!sum) //不需要染色 
			return 0;
		if(flag) //无法完成二分图染色，一定可以三染色 
			return 3;
		if(both) //需要两种颜色 
			return 2;
		return 1;
	}
};