#include <algorithm>
using namespace std;
class PyramidSequences
{
public:
	int Gcd(int a, int b)
	{
		return a ? Gcd(b % a, a) : b;
	}
	long long distinctPairs(int n, int m)
	{
		if(n > m)
			swap(n, m);
		int k = Gcd(n - 1, m - 1) * 2; //同余方程有解，要求k能整除a+b或a-b，即a与b的模k的余数相同或互补 
		int x = n / k, y = m / k;
		n %= k, m %= k; //按每种余数的出现次数考虑 
		long long ans = 0;
		if(n > m)
			swap(n, m), swap(x, y);
		ans += (long long)n * (x + 1) * (y + 1); //余数相同的对数 
		ans += (long long)(m - n) * x * (y + 1);
		ans += (long long)(k - m) * x * y;
		ans -= (long long)(x + (n > k / 2)) * (y + (m > k / 2)); //减去既相同又互补的对数 
		n = max(n - 1, 0);
		m = k - m;
		k--;
		m = min(m, k);
		if(n > m) //余数互补的对数 
		{
			ans += (long long)m * (x + 1) * y;
			ans += (long long)(n - m) * (x + 1) * (y + 1);
			ans += (long long)(k - n) * x * (y + 1);
		}
		else
		{
			ans += (long long)n * (x + 1) * y;
			ans += (long long)(m - n) * x * y;
			ans += (long long)(k - m) * x * (y + 1);
		}
		return ans;
	}
};