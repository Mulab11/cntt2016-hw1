#include <algorithm>
using namespace std;
const int mod = 1000000007;
class DefectiveAddition
{
public:
	int n;
	void Add(int &x, int y)
	{
		x = (x + y) % mod;
	}
	int count(vector<int> a, int m)
	{
		n = a.size();
		for(int i = 0; i < n; i++)
			a[i]++;
		int ans = 0, mask_high = 0, mask_low = (1 << 30) - 1;
		for(int k = 1 << 30; k; mask_high += k, k >>= 1, mask_low -= k) //枚举前若干位均达到上边界时的情况 
		{
			int xor_high = 0;
			for(int i = 0; i < n; i++)
				xor_high ^= a[i] & mask_high;
			if(xor_high != (m & mask_high))
				break;
			int tot = 0, f[51][51] = {0}; //f[i][j]表示前i个数在当前位上取了j个1时，所有达到上边界的数对应的低位方案数的乘积 
			f[0][0] = 1;
			for(int i = 0; i < n; i++)
			{
				if(a[i] & k)
					tot++;
				for(int j = 0; j < n; j++)
				{
					if(a[i] & k)
					{
						Add(f[i + 1][j], f[i][j]);
						Add(f[i + 1][j + 1], (long long)f[i][j] * (a[i] & mask_low) % mod);
					}
					else
						Add(f[i + 1][j], (long long)f[i][j] * (a[i] & mask_low) % mod);
				}
			}
			for(int i = tot - 1, j = 1; i >= 0; i--, j = (long long)j * (mask_low + 1) % mod)
			{ //若存在当前位未达上边界的数，答案可以直接计算 
				if(((m & k) > 0) == (i & 1))
					Add(ans, (long long)f[n][i] * j % mod);
			}
		}
		for(int i = 0; i < n; i++)
			m ^= a[i] - 1;
		if(!m) //判断所有数均达到上边界是否满足要求 
			ans++;
		return ans;
	}
};
