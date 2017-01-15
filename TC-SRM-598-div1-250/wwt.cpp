#include <bits/stdc++.h>

using namespace std;

class BinPacking
{
public:
	int minBins(vector<int> item)
	{
		int v1 = 0;
		for(auto p : item)
			if (p == 100) ++ v1;
		int ans = (1 << 30);
		for(int us = 0;us <= v1;us ++) //假设我们拿出来us个100，让他们自己3个3个组成1组
		{
			int cur = us / 3 + bool(us % 3);
			vector<int> a;
			a.clear();
			for(auto p : item) if (p != 100) a.push_back(p);
			for(int i = 1;i <= v1 - us;i ++) a.push_back(100);//剩下的1和别人一起组，那么一组最多两个数
			sort(a.begin(),a.end());//排序，贪心
			static bool put[55];
			memset(put,0,sizeof put);
			for(int i = 0,j = a.size() - 1;i < a.size();i ++)
				if (put[i]) continue; else
				{
					for(;i < j && (put[j] || a[i] + a[j] > 300);j --);//找到一个最大的能和i匹配的组成一组
					if (i < j) put[j] = 1;
					++ cur;
				}
			ans = min(ans,cur);
		}
		return ans;
	}
};
