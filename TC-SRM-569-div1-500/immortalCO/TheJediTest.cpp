#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

class TheJediTest
{
public:
	int minimumSupervisors(vector<int> val, int k)
	{
		// 考虑贪心
		// 暴力枚举每一条边是从左往右还是从右往左
		int n = val.size(), ans = 2e9;
		for(int s = 0; s != (1 << (n - 1)); ++s)
		{
			int cur = 0, pre = 0;
			for(int i = 0; i + 1 != n; ++i)
			{
				pre += val[i];
				if(s & (1 << i))
				{
					// 从左往右：获取
					// 争取把剩下的东西模掉
					int tmp = min(k - pre % k, val[i + 1]);
					cur += (pre + tmp + k - 1) / k;
					pre = -tmp;
				}
				else
				{
					// 把剩下的东西全给下一个
					int tmp = min(pre % k, val[i]);
					cur += (pre - tmp + k - 1) / k;
					pre  = tmp;
				}
			}
			pre += val.back();
			cur += (pre + k - 1) / k;
			ans = min(ans, cur);
		}
		return ans;
	}
}	user;
