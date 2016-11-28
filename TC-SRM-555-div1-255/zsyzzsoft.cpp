#include <algorithm>
using namespace std;
class CuttingBitString
{
public:
	int n, f[51];
	int getmin(string s)
	{
		n = s.length();
		for(int i = n - 1; i >= 0; i--) //动态规划 
		{
			f[i] = 100;
			long long t = 0;
			for(int j = i + 1; j <= n; j++)
			{
				t = t * 2 + (s[j - 1] - '0');
				if(!t) //前导0 
					break;
				long long tmp = t;
				while(t % 5 == 0) //判断是否为5的幂 
					t /= 5;
				if(t == 1)
					f[i] = min(f[i], f[j] + 1);
				t = tmp;
			}
		}
		return f[0] < 100 ? f[0] : -1;
	}
};
