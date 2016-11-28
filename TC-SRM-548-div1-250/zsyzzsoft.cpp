#include <algorithm>
using namespace std;
class KingdomAndTrees
{
public:
	int n, h[51];
	bool Check(int k)
	{
		int d[51] = {0};
		for(int i = 1; i <= n; i++) //设置尽量小的高度 
			d[i] = max(d[i - 1] + 1, h[i] - k);
		for(int i = 1; i <= n; i++)
		{
			if(abs(d[i] - h[i]) > k)
				return false;
		}
		return true;
	}
	int minLevel(vector<int> heights)
	{
		n = heights.size();
		for(int i = 1; i <= n; i++)
			h[i] = heights[i - 1];
		int l = 0, r = 1000000000;
		while(l < r) //二分 
		{
			int mid = (l + r) / 2;
			if(Check(mid))
				r = mid;
			else
				l = mid + 1;
		}
		return l;
	}
};