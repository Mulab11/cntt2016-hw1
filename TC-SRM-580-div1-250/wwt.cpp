#include <bits/stdc++.h>

using namespace std;

class EelAndRabbit
{
public:
	bool ok(int T,int t,int l)
	{
		return T - t - l <= 0 && T - t >= 0;
	}

	int getmax(vector<int> l, vector<int> t)
	{
		vector<int> po;//the useful time
		po.clear();
		int n = l.size();
		for(int i = 0;i < n;i ++)
			po.push_back(t[i]),po.push_back(t[i] + l[i]); //t_i <= T <= t_i + l_i
		int ans = 0;
		for(int i = 0;i < po.size();i ++)
			for(int j = i;j < po.size();j ++) //enumerate two time to catch
			{
				int cur = 0;
				int T = po[i],T1 = po[j];
				for(int k = 0;k < n;k ++)
					if (ok(T,t[k],l[k]) || ok(T1,t[k],l[k])) ++ cur;
				ans = max(ans,cur);
			}
		return ans;
	}
};
