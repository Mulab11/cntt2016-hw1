#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int f[10][1010];

class IncrementAndDoubling
{
public:
	int getMin(vector<int> arr)
	{
		int n = (int) arr.size();
		// 用背包处理
		for(int i = 1; i <= 1000; ++i) f[0][i] = i;
		for(int k = 1; k != 10; ++k)
		{
			int v = 1 << k;
			memcpy(f[k] + 1, f[k - 1] + 1, 4000);
			for(int i = v; i <= 1000; ++i)
				f[k][i] = min(f[k][i], f[k][i - v] + 1);
		}
		int ans = 1 << 30;
		// *2 的次数不会太多，可以枚举
		for(int k = 0; k != 10; ++k)
		{
			int sum = k;
			for(int i = 0; i != n; ++i)
				sum += f[k][arr[i]];
			ans = min(ans, sum);
		}
		return ans;
	}
}	user;
