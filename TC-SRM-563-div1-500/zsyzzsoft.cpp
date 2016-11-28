#include <algorithm>
using namespace std;
class SpellCards
{
public:
	int maxDamage(vector<int> level, vector<int> damage)
	{
		int n = level.size(), f[51][51] = {0};
		for(int i = 1; i <= n; i++) //level之和不超过n的背包 
		{
			for(int j = 0; j <= n; j++)
			{
				f[i][j] = f[i - 1][j];
				if(level[i - 1] <= j)
					f[i][j] = max(f[i][j], f[i - 1][j - level[i - 1]] + damage[i - 1]);
			}
		}
		return f[n][n];
	}
};
