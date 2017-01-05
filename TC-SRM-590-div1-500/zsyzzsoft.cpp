#include <algorithm>
using namespace std;
class XorCards
{
public:
	long long numberOfWays(vector<long long> a, long long limit)
	{
		int n = a.size(), i = 0, j;
		for(long long t = 1LL << 62; t; t >>= 1) //高斯消元
		{
			for(j = i; j < n && !(a[j] & t); j++);
			if(j == n)
				continue;
			swap(a[i], a[j]);
			for(j = 0; j < n; j++)
			{
				if(j != i && a[j] & t)
					a[j] ^= a[i];
			}
			i++;
		}
		long long ans = 0, cur = 0;
		for(i = 0; i < n; i++)
		{
			if((cur ^ a[i]) <= limit)
			{
				cur ^= a[i]; //如果取了这个数，继续考虑后面的 
				ans += 1LL << (n - i - 1); //如果没取这个数，后面的可以随便取 
			}
		}
		return ans + 1;
	}
};