#include <algorithm>
#include <map>
using namespace std;
bool prime[1000001];
int m, pr[1000000];
class HolyNumbers
{
public:
	long long Dfs(int depth, long long n)
	{
		if(depth == m)
			return 1;
		if((long long)pr[depth] * pr[depth + 1] > n) //只能选一个质数了 
			return upper_bound(pr + depth, pr + m, n) - (pr + depth) + 1;
		int p = pr[depth];
		long long ans = Dfs(depth + 1, n);
		for(long long i = 1; i <= n && (i *= p) <= n; i *= p)
			ans += Dfs(depth + 1, n / i);
		return ans;
	}
	long long count(long long n, int p)
	{
		for(int i = 2; i <= p; i++)
			prime[i] = true;
		for(int i = 2; i <= p; i++)
		{
			if(!prime[i])
				continue;
			pr[m++] = i;
			for(int j = i + i; j <= p; j += i)
				prime[j] = false;
		}
		return Dfs(0, n);
	}
};