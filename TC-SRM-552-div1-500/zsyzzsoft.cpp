#include <algorithm>
using namespace std;
const int inf = -1000000000;
int area[31][31][3], f[31][1801] = {0}, g[31][1801] = {0};;
class FoxAndFlowerShopDivOne
{
public:
	int n, m, cur_diff;
	int Check(int l, int b, int r, int t)
	{
		int x = area[r][t][1] - area[l][t][1] - area[r][b][1] + area[l][b][1],
			y = area[r][t][2] - area[l][t][2] - area[r][b][2] + area[l][b][2];
		cur_diff = x - y + 900;
		return x + y;
	}
	int Solve(vector<string> map, int diff)
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
				map[i][j] = map[i][j] == '.' ? 0 : map[i][j] == 'L' ? 1 : 2;
		}
		for(int i = 1; i <= n; i++) //二维前缀和 
		{
			for(int j = 1; j <= m; j++)
			{
				for(int k = 0; k < 3; k++)
					area[i][j][k] = area[i - 1][j][k] + area[i][j - 1][k] - area[i - 1][j - 1][k];
				area[i][j][(int)map[i - 1][j - 1]]++;
			}
		}
		for(int i = 0; i <= 1800; i++)
			f[0][i] = g[n][i] = inf;
		for(int i = 1; i < n; i++) //计算上半部分在每种差值情况下的答案 
		{
			for(int j = 0; j <= 1800; j++)
				f[i][j] = f[i - 1][j];
			for(int l = 0; l < i; l++)
			{
				for(int b = 0; b < m; b++)
				{
					for(int t = b + 1; t <= m; t++)
					{
						int tmp = Check(l, b, i, t);
						f[i][cur_diff] = max(tmp, f[i][cur_diff]);
					}
				}
			}
		}
		for(int i = n - 1; i > 0; i--) //计算下半部分在每种差值情况下的答案 
		{
			for(int j = 0; j <= 1800; j++)
				g[i][j] = g[i + 1][j];
			for(int r = i + 1; r <= n; r++)
			{
				for(int b = 0; b < m; b++)
				{
					for(int t = b + 1; t <= m; t++)
					{
						int tmp = Check(i, b, r, t);
						g[i][cur_diff] = max(tmp, g[i][cur_diff]);
					}
				}
			}
		}
		int ans = -1;
		for(int k = 1; k < n; k++) //枚举分割线 
		{
			for(int i = 0; i <= 1800; i++)
			{
				for(int j = 0; j <= 1800; j++)
				{
					if(abs(i + j - 1800) <= diff)
						ans = max(ans, f[k][i] + g[k][j]);
				}
			}
		}
		return ans;
	}
	int theMaxFlowers(vector<string> map, int diff)
	{
		n = map.size(), m = map[0].length();
		int ans = Solve(map, diff);
		vector<string> map_t;
		for(int i = 0; i < m; i++) //转置再做一遍 
		{
			string str;
			for(int j = 0; j < n; j++)
				str += map[j][i];
			map_t.push_back(str);
		}
		swap(n, m);
		return max(ans, Solve(map_t, diff));
	}
};
