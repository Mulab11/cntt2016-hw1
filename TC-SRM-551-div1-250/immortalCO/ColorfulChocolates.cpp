#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int solve(vector<int> pos, int lim)
{
	int ans = 0;
	for(int p = 0; p != (int) pos.size(); ++p)
	{
		// 可以认为点是可以穿越的，并且移动独立
		// 并且至少有一个不动点
		// 那我们枚举这个不动点
		vector<int> mov;
		for(int i = p - 1, c = pos[p] - 1; i >= 0; --i, --c)
			mov.push_back(c - pos[i]);
		for(int i = p + 1, c = pos[p] + 1; i < (int) pos.size(); ++i, ++c)
			mov.push_back(pos[i] - c);
		sort(mov.begin(), mov.end());
		int ret = 1;
		for(int i = 0, use = lim; i != (int) mov.size(); ++i)
			if((use -= mov[i]) >= 0) ++ret; else break;
		if(ans < ret) ans = ret;
	}
	return ans;
}

class ColorfulChocolates
{
public:
	int maximumSpread(string val, int lim)
	{
		int ans = 1;
		// 每种字母分开来考虑
		for(int w = 'A'; w <= 'Z'; ++w)
		{
			vector<int> pos;
			for(int i = 0; i != (int) val.size(); ++i)
				if(val[i] == w) pos.push_back(i);
			if(!pos.empty()) ans = max(ans, solve(pos, lim));
		}
		return ans;
	}
}	user;
