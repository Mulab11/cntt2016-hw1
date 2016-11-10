#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

class BinPacking
{
public:
	int minBins(vector<int> inp)
	{
		int A = 0, B = 0;
		vector<int> Val;
		for(int i = 0; i != (int) inp.size(); ++i)
		{
			// 超过 200 的只能一个，恰为 100 的可以 3 个一组
			if(inp[i] > 200) ++A;
			else if(inp[i] == 100) ++B;
			else Val.push_back(inp[i]);
		}
		int ret = 1000000;
		// 枚举 3 个为一组的 100 的个数
		for(int U = 0; U <= B; U += 3)
		{
			int ans = A + U / 3;
			vector<int> val = Val;
			for(int i = 0; i != B - U; ++i) val.push_back(100);
			sort(val.begin(), val.end());
			// 剩下的两个两个贪心配对
			for(int i = 0; i != (int) val.size(); ++i) if(val[i] != -1)
				for(int j = val.size(); j--; ) if(val[j] != -1 && val[i] + val[j] <= 300)
				{++ans, val[i] = val[j] = -1; break;}
			for(int i = 0; i != (int) val.size(); ++i) if(val[i] != -1) ++ans;
			if(ans < ret) ret = ans;
		}
		return ret;
	}
}	user;
