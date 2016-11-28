#include <algorithm>
#include <map>
using namespace std;
const int p = 1000000009;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
bool vis[40][40];
int width[41][4], pw[2000];
class CoinsGame
{
public:
	int n, m, map[40][40], sz, l, r, b, t;
	bool free;
	void Dfs(int x, int y)
	{
		if(x < 0 || x >= n || y < 0 || y >= m)
		{
			free = true;
			return;
		}
		if(vis[x][y] || !map[x][y])
			return;
		vis[x][y] = true;
		sz++;
		l = min(l, x), r = max(r, x), b = min(b, y), t = max(t, y);
		for(int i = 0; i < 4; i++)
			Dfs(x + dx[i], y + dy[i]);
	}
	int Subset(int x)
	{
		return (pw[x] + p - x - 1) % p;
	}
	int ways(vector<string> board)
	{
		n = board.size(), m = board[0].size();
		int blank = 0, closed = 0;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
				blank += map[i][j] = board[i][j] == '.';
		}
		pw[0] = 1;
		for(int i = 1; i <= blank; i++)
			pw[i] = pw[i - 1] * 2 % p;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				sz = 0;
				free = false;
				l = r = i;
				b = t = j;
				Dfs(i, j);
				if(!free) //封闭区域 
					closed += sz;
				else if(sz == (r - l + 1) * (t - b + 1)) //矩形区域 
				{
					if(l && r < n - 1) //左右有封闭边界 
					{
						if(b)
							width[m - b][0] += r - l + 1;
						else
							width[b + 1][1] += r - l + 1;
					}
					else if(b && t < m - 1) //上下有封闭边界 
					{
						if(l)
							width[n - l][2] += t - b + 1;
						else
							width[l + 1][3] += t - b + 1;
					}
				}
			}
		}
		int ans = (Subset(blank) + p - Subset(closed)) % p;
		for(int i = 1; i <= 40; i++)
		{
			for(int j = 0; j < 4; j++)
				ans = (ans + p - (long long)i * Subset(width[i][j]) % p) % p;
		}
		return ans;
	}
};
