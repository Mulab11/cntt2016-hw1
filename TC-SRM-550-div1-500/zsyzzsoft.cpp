#include <algorithm>
using namespace std;
class CheckerExpansion
{
public:
	long long t;
	long long Count(long long n) //求n!中因子2的个数 
	{
		long long ret = 0;
		for(long long t = 1LL << 50; t > 1; t >>= 1)
			ret += n / t;
		return ret;
	}
	bool Check(long long n, long long m) //判断C(n, m)的奇偶性 
	{
		return Count(n) - Count(m) - Count(n - m) == 0;
	}
	char Solve(long long x, long long y)
	{
		if(x < y || (x - y) % 2)
			return '.';
		long long a = (x - y) / 2, b = y; //横向偏移次数与斜向偏移次数 
		if(a + b >= t)
			return '.';
		if(!Check(a + b, a))
			return '.';
		return (a + b) % 2 ? 'B' : 'A';
	}
	vector<string> resultAfter(long long _t, long long x0, long long y0, int w, int h)
	{
		t = _t;
		vector<string> ans;
		for(int i = 0; i < h; i++)
		{
			string cur;
			for(int j = 0; j < w; j++)
				cur += Solve(x0 + j, y0 + h - i - 1);
			ans.push_back(cur);
		}
		return ans;
	}
};
