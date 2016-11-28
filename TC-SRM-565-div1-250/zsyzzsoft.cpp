#include <algorithm>
using namespace std;
long long f[51][101];
class MonstersValley
{
public:
	int minimumPrice(vector<long long> a, vector<int> b)
	{
		int n = a.size();
		for(int i = n - 1; i >= 0; i--)
		{
			for(int j = 0; j <= n * 2; j++)
			{
				f[i][j] = max(f[i + 1][j], a[i]);
				if(j >= b[i])
					f[i][j] = min(f[i][j], max(f[i + 1][j - b[i]] - a[i], 0LL));
			}
		}
		for(int i = 0; i <= n * 2; i++)
		{
			if(f[0][i] == 0)
				return i;
		}
		return -1;
	}
};
