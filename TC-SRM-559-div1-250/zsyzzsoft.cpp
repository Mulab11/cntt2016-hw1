#include <algorithm>
using namespace std;
class HyperKnight
{
public:
	bool Legal(int x, int y, int n, int m) //判断目标位置是否合法 
	{
		return x >= 0 && x < n && y >= 0 && y < m;
	}
	long long countCells(int a, int b, int n, int m, int k)
	{
		const int dx[8] = {a, a, -a, -a, b, b, -b, -b}, dy[8] = {b, -b, b, -b, a, -a, a, -a};
		int x[6] = {0, a, b, n - a, n - b, n}, y[6] = {0, a, b, m - a, m - b, m};
		sort(x, x + 6);
		sort(y, y + 6);
		long long ans = 0;
		for(int i = 0; i < 5; i++) //枚举区块 
		{
			for(int j = 0; j < 5; j++)
			{
				int moves = 0;
				for(int t = 0; t < 8; t++)
					moves += Legal(x[i] + dx[t], y[j] + dy[t], n, m);
				if(moves == k)
					ans += (long long)(x[i + 1] - x[i]) * (y[j + 1] - y[j]);
			}
		}
		return ans;
	}
};
