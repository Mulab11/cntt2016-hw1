#include <algorithm>
#include <math.h>
using namespace std;
const int div_max = 20000, pw_max = 500000;
bool pw2[pw_max], pw3[pw_max];
class SemiPerfectPower
{
public:
	vector<int> div[div_max], cnt[div_max];
	int mob[div_max];
	int Gcd(int a, int b)
	{
		return a ? Gcd(b % a, a) : b;
	}
	int Root(long long x)
	{
		long long l = 0, r = x;
		while(l < r)
		{
			long long mid = (l + r + 1) / 2;
			if(x / mid / mid)
				l = mid;
			else
				r = mid - 1;
		}
		return l;
	}
	int CubeRoot(long long x)
	{
		long long l = 0, r = x;
		while(l < r)
		{
			long long mid = (l + r + 1) / 2;
			if(x / mid / mid / mid)
				l = mid;
			else
				r = mid - 1;
		}
		return l;
	}
	long long Solve(long long n)
	{
		long long ans = 0;
		for(int i = 1; (long long)i * i * i <= n; i++) //求形式为i*x^2的个数 
		{
			if(!pw2[i])
				ans += Root(n / i) - i;
		}
		for(int i = 1; (long long)i * i * i * i <= n; i++) //求形式为i*x^3的个数 
		{
			if(pw3[i])
				continue;
			int p = CubeRoot(n / i);
			for(int k = CubeRoot(i); k >= 1; k--) //i*x的最大平方因子为k^2，k^3不得超过i 
			{
				int u = i / Gcd(k * k, i);
				if(pw2[u])
					continue;
				int t = k * k / Gcd(k * k, i), l = i / t, v = p / t; //x: (i, v], !pw2[x], (u, x) = 1
				for(unsigned j = 0; j < div[u].size(); j++) //枚举约数容斥 
				{
					int x = div[u][j];
					ans += mob[x] * (cnt[x][v / x] - cnt[x][l / x]);
				}
			}
		}
		return ans;
	}
	long long count(long long l, long long r)
	{
		for(int i = 1; i < div_max; i++)
		{
			for(int j = i; j < div_max; j += i)
				div[j].push_back(i);
		}
		for(int i = 2, x; (x = i * i) < pw_max; i++)
		{
			for(int j = x; j < pw_max; j += x)
				pw2[j] = true;
		}
		for(int i = 2, x; (x = i * i * i) < pw_max; i++)
		{
			for(int j = x; j < pw_max; j += x)
				pw3[j] = true;
		}
		mob[1] = 1;
		for(int i = 2; i < div_max; i++) //预处理莫比乌斯函数 
		{
			if(pw2[i])
				mob[i] = 0;
			else
				mob[i] = -mob[i / div[i][1]];
		}
		for(int i = 1; i < div_max; i++)
		{
			cnt[i].push_back(0);
			for(int j = i, k = 0; j < pw_max; j += i) //预处理i的倍数中不含平方因子的个数的前缀和 
				cnt[i].push_back(k += !pw2[j]);
		}
		return Solve(r) - Solve(l - 1);
	}
};