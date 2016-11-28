#include <algorithm>
#include <memory.h>
using namespace std;
bool prime[50000];
int sg[1000001], num[1000001], cnt[256];
class TheDivisionGame
{
public:
	long long countWinningIntervals(int l, int r)
	{
		memset(prime, 1, sizeof(prime));
		int n = r - l + 1;
		for(int i = 0; i < n; i++)
			num[i] = l + i;
		for(int i = 2; i < 50000; i++) //筛质因子 
		{
			if(!prime[i])
				continue;
			for(int j = i + i; j < 50000; j += i)
				prime[j] = false;
			for(long long p = i; p <= r; p *= i)
			{
				for(int j = (p - l % p) % p; j < n; j += p)
					sg[j]++, num[j] /= i;
			}
		}
		for(int i = 0; i < n; i++)
			sg[i] += num[i] > 1;
		long long ans = 0;
		cnt[0] = 1;
		for(int i = 0, j = 0; i < n; i++) //计算前缀异或，统计答案 
			ans += cnt[j ^= sg[i]]++;
		return (long long)n * (n + 1) / 2 - ans;
	}
};
