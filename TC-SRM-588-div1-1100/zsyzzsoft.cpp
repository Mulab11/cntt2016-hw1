#include <algorithm>
#include <memory.h>
using namespace std;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
bool map[52][52], vis[52][52];
class GameInDarknessDiv1
{
public:
	int n, m, ax, ay, bx, by, disa[52][52], disb[52][52], dep[52][52];
	void DisA(int x, int y)
	{
		vis[x][y] = true;
		for(int i = 0; i < 4; i++)
		{
			int nx = x + dx[i], ny = y + dy[i];
			if(map[nx][ny] && !vis[nx][ny])
				disa[nx][ny] = disa[x][y] + 1, DisA(nx, ny);
		}
	}
	void DisB(int x, int y)
	{
		vis[x][y] = true;
		for(int i = 0; i < 4; i++)
		{
			int nx = x + dx[i], ny = y + dy[i];
			if(map[nx][ny] && !vis[nx][ny])
				disb[nx][ny] = disb[x][y] + 1, DisB(nx, ny);
		}
	}
	int Depth(int x, int y, bool root = false)
	{
		vis[x][y] = true;
		dep[x][y] = 1;
		int ret = 0;
		for(int i = 0; i < 4; i++)
		{
			int nx = x + dx[i], ny = y + dy[i];
			if(map[nx][ny] && !vis[nx][ny])
			{
				Depth(nx, ny);
				dep[x][y] = max(dep[x][y], dep[nx][ny] + 1);
				if(root && dep[nx][ny] >= 3)
					ret++;
			}
		}
		return ret;
	}
	string check(vector<string> field)
	{
		n = field.size(), m = field[0].size();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				map[i + 1][j + 1] = field[i][j] != '#';
				if(field[i][j] == 'A')
					ax = i + 1, ay = j + 1;
				else if(field[i][j] == 'B')
					bx = i + 1, by = j + 1;
			}
		}
		memset(vis, 0, sizeof(vis)); //计算AB到各点的距离 
		DisA(ax, ay);
		memset(vis, 0, sizeof(vis));
		DisB(bx, by);
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(disa[i][j] >= disb[i][j] + 2) //Bob可以走到该点 
				{
					memset(vis, 0, sizeof(vis));
					if(Depth(i, j, true) >= 3) //判断当前点是否存在3个深度至少为3的子树，这是Bob可以围绕该点躲开Alice的充要条件 
						return "Bob wins";
				}
			}
		}
		return "Alice wins";
	}
};