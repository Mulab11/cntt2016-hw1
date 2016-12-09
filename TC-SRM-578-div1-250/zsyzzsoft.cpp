#include <algorithm>
using namespace std;
const int p = 1000000007;
bool vis[50][50];
class GooseInZooDivOne
{
public:
	int n, m, d, area;
	vector<string> field;
	void Dfs(int x, int y)
	{
		vis[x][y] = true;
		area++;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(field[i][j] == 'v' && !vis[i][j] && abs(i - x) + abs(j - y) <= d)
					Dfs(i, j);
			}
		}
	}
	int count(vector<string> _field, int dist)
	{
		field = _field;
		n = field.size(), m = field[0].size(), d = dist;
		int a = 0, b = 0;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(field[i][j] == 'v' && !vis[i][j])
				{
					area = 0;
					Dfs(i, j); //处理连通块 
					if(area & 1)
						a++; //奇数 
					else
						b++; //偶数 
				}
			}
		}
		int ans = 1; //计算答案 
		for(int i = 1; i < a; i++)
			ans = ans * 2 % p;
		for(int i = 0; i < b; i++)
			ans = ans * 2 % p;
		return (ans + p - 1) % p;
	}
};