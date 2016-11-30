#include <algorithm>
using namespace std;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
class Tunnels
{
public:
	int n, m, cnt, map[50][50];
	int Dfs(int x, int y, int lx = -1, int ly = -1) //找连通块，并返回末端高度 
	{
		if(lx < 0)
			cnt = 0;
		cnt++;
		for(int i = 0; i < 4; i++)
		{
			int nx = x + dx[i], ny = y + dy[i];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && map[nx][ny] && (nx != lx || ny != ly))
				return Dfs(nx, ny, x, y);
		}
		if(!x && cnt != m)
			return -1;
		return x;
	}
	int minimumTunnels(vector<string> frame)
	{
		n = frame.size(), m = frame[0].size();
		if(m == 1)
		{
			for(int i = 1; i < (n = frame.size()); i++)
			{
				if(frame[i] == frame[i - 1])
					frame.erase(frame.begin() + i--);
			}
		}
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
				map[i][j] = frame[i][j] == 'X';
		}
		int ans = 0, l[50] = {0}, r[50] = {0}, f[51][51][51] = {0};
		for(int i = 0; i < n; i++)
		{
			if(map[i][0])
			{
				if(Dfs(i, 0) == i && cnt == m)
					l[i] = r[i] = -1; //方向不定的地道 
				else if(i + 1 < n && !map[i + 1][0] && (!i || !map[i - 1][0] || !map[i][1]) && Dfs(i, 0) < i)
					l[i] = Dfs(i, 0) < 0 || cnt > 2; //可以继续向下打 
				else if(i && !map[i - 1][0] && (i == n - 1 || !map[i + 1][0] || !map[i][1]) && Dfs(i, 0) >= i)
					l[i] = 2; //必须是从上面打下来的 
			}
			if(map[i][m - 1])
			{
				if(Dfs(i, m - 1) == i && cnt == m)
					l[i] = r[i] = -1;
				else if(i + 1 < n && !map[i + 1][m - 1] && (!i || !map[i - 1][m - 1] || !map[i][m - 2]) && Dfs(i, m - 1) < i)
					r[i] = Dfs(i, m - 1) < 0 || cnt > 2;
				else if(i && !map[i - 1][m - 1] && (i == n - 1 || !map[i + 1][m - 1] || !map[i][m - 2]) && Dfs(i, m - 1) >= i)
					r[i] = 2;
			}
		}
		for(int i = 0; i < m; i++)
		{
			if(map[0][i] && (!i || !map[0][i - 1]))
				ans++;
		}
		for(int i = n - 1; i >= 0; i--) //按左右两边的插头情况动态规划 
		{
			for(int u = 0; u < n; u++)
			{
				for(int v = 0; v < n; v++)
				{
					int cu = u, cv = v, w = 0;
					if(l[i] == 1)
						cu++;
					else if(l[i] == 2)
					{
						if(cu)
							cu--;
						else
							w++;
					}
					if(r[i] == 1)
						cv++;
					else if(r[i] == 2)
					{
						if(cv)
							cv--;
						else
							w++;
					}
					if(l[i] < 0)
						f[i][u][v] = min(f[i + 1][u - (u && i)][v + 1] + (!u && i), f[i + 1][u + 1][v - (v && i)] + (!v && i));
					else
						f[i][u][v] = f[i + 1][cu][cv] + w;
				}
			}
		}
		return f[0][0][0] + ans;
	}
};