/*
由于我们只关心一个值v在第二个dice中有多少值比v小，所以我们最多只有n^2种值。由于我们可以任意填0，所以我们可以设cnt[v]表示要凑出v的和，
最少要用多少位置，那么，假如最后cnt[v]<=空的个数，这个v就是可以用的。算cnt[v]可以用简单的背包即可。
*/
#include <bits/stdc++.h>

using namespace std;

class KingdomAndDice
{
public:
	double newFairness(vector <int> firstDie, vector <int> secondDie, int X)
	{
		sort(secondDie.begin(),secondDie.end());
		int n = firstDie.size(),m = 0,sum = 0;
		for(int i = 0;i < n;i ++)
			if (firstDie[i]) sum += lower_bound(secondDie.begin(),secondDie.end(),firstDie[i]) - secondDie.begin(); else
				++ m;
		static int cnt[3005];
		for(int i = 1;i <= n * n;i ++) cnt[i] = m + 1;
		//背包
		for(auto p = secondDie.begin();p != secondDie.end();p ++)
		{
			int l = (*p) + 1,r = ((p + 1) == secondDie.end()) ? X : (*(p + 1)) - 1,num = p - secondDie.begin() + 1;
			int co = r - l + 1;
			for(int j = 0;j < firstDie.size();j ++)
				if (firstDie[j] >= l && firstDie[j] <= r) -- co;
			for(int j = 0;j < min(co,m);j ++) //枚举num这个物品用了多少个。
				for(int v = n * n;v >= num;v --)
					cnt[v] = min(cnt[v],cnt[v - num] + 1);
		}
		double tmp = 1.1,ans;
		for(int v = 0;v <= n * n;v ++)
			if (cnt[v] <= m)
			{
				double cur = fabs((v + sum) / (double(n) * n) - 0.5);
				if (cur - tmp < -1e-9) tmp = cur,ans = (v + sum) / (double(n) * n);
			}
		return ans;
	}	
};
