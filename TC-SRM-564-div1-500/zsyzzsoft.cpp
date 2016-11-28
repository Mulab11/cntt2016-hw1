#include <algorithm>
using namespace std;
class AlternateColors2
{
public:
	int Count(int l, int r)
	{
		return l <= r ? r - l + 1 : 0;
	}
	long long countWays(int n, int k)
	{
		long long ans = 0;
		if(k % 3 == 1) //三种颜色均未耗尽 
		{
			for(int x = k; x <= n; x++)
				ans += Count(k, n - x - k);
		}
		for(int x = 0; x * 3 < k; x++) //一种颜色已耗尽 
		{
			if((k - x * 3) % 2 == 0)
				continue;
			int t = (k - x * 3 + 1) / 2;
			ans += Count(x + t, n - x * 2 - t) * 2;
		}
		for(int x = 0; x * 2 < k; x++) //两种颜色都已耗尽 
		{
			if(x * 3 < k)
				ans++;
			ans += Count(0, min(x - 1, k - x * 2 - 1)) * 2;
		}
		return ans;
	}
};
