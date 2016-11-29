#include <algorithm>
using namespace std;
class XorAndSum
{
public:
	int n;
	long long maxSum(vector<long long> a)
	{
		n = a.size();
		int i = 0, j;
		long long ans = 0;
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
		for(i = 1; i < n; i++) //计算答案
			a[0] ^= a[i];
		for(i = 1; i < n; i++)
			ans += a[i] ^= a[0];
		return ans + a[0];
	}
};