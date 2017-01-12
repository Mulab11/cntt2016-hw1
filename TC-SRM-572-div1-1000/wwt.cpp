#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pi;

class NextAndPrev
{
public:
	int getMinimum(int nextCost, int prevCost, string start, string goal)
	{
		if (start == goal) return 0;//corner case
		static int apear[55];
		memset(apear,0,sizeof apear);
		for(auto p:goal) apear[p - 'a'] = 1;
		bool ok = 0;
		for(int i = 0;i < 26;i ++)
			if (!apear[i]) ok = 1;
		if (!ok) return -1; //if goal = {'a'..'z'},then it is impossible to trans start->goal
		static int go[55];//find the map from the start to the goal
		memset(go,255,sizeof go);
		for(int i = 0;i < start.length();i ++)
		{
			int u = start[i] - 'a',v = goal[i] - 'a';
			if (go[u] == -1) go[u] = v; else
				if (go[u] != v) return -1;//same start char but different goal char
		}
		vector<pi> lis;
		lis.clear();
		for(int i = 0;i < 26;i ++)
			if (go[i] != -1) lis.push_back(pi(i,go[i]));
		int ans = (1 << 30);
		for(int i = 0;i < 26;i ++) //rotate the start
		{
			sort(lis.begin(),lis.end());
			bool ok = 1;
			for(int j = 0;j < lis.size() - 1;j ++)
				if (lis[j].second > lis[j + 1].second) {ok = 0;break;} //only if the goal is increasing we can transform the start to goal
			if (ok)
			{
				for(int j = -2;j <= 2;j ++)
				{
					int cost = 0;
					for(int k = 0;k < lis.size();k ++) lis[k].second += j * 26; //assume that the goal can be shifted (to handle the situation that the char can shift left or right)
					for(int k = 0,p = 0;k < lis.size();)
					{
						for(;lis[p].second == lis[k].second && p < lis.size();p ++);
						int low = lis[k].first,high = lis[p - 1].first;
						cost += max(lis[k].second - low,0) * nextCost + max(high - lis[k].second,0) * prevCost;		
						k = p;
					}	
					ans = min(ans,cost);
					for(int k = 0;k < lis.size();k ++) lis[k].second -= j * 26; //recover
				}
			}
			lis[0].first += 26;//rotate the first 
		}
		return (ans == (1 << 30)) ? -1 : ans;
	}
};
