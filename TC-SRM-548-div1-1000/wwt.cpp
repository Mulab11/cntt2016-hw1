/*
	二分答案，贪心维护当前结尾最小可以是多少。
*/
#include <bits/stdc++.h>

using namespace std;

class KingdomAndTrees
{
public:
	bool test(vector<int> heights,int lim)
	{
		int lst = 0;
		for(int i = 0,n = heights.size();i < n;i ++)
		{
			int cur = heights[i];
			if (cur > lst) lst = max(lst + 1,cur - lim); else
			{
				if (cur + lim <= lst) return 0;
				lst ++;
			}
		}
		return 1;
	}

	int minLevel(vector<int> heights)
	{
		int l = 0,r = int(1e9) + 5,tmp;
		for(int mid;l <= r;)
		{
			mid = l + r >> 1;
			if (test(heights,mid)) tmp = mid,r = mid - 1; else l = mid + 1;
		}
		return tmp;
	}
};
