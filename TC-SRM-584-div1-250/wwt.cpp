#include <bits/stdc++.h>

using namespace std;

class Egalitarianism
{
public:
	int a[55][55];
	int maxDifference(vector<string> isFriend, int d)
	{
		int n = isFriend.size();
		memset(a,60,sizeof a);
		int inf = a[0][0];
		//|a_x-a_y|<=d,|a_y-a_z|<=d ----> |a_x - a_z|<=2d
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < n;j ++)
				if (isFriend[i][j] == 'Y') a[i][j] = 1;
		//floyd to get the shortest path(which is equivalent to limits)
		for(int k = 0;k < n;k ++)
			for(int i = 0;i < n;i ++)
				for(int j = 0;j < n;j ++)
					a[i][j] = min(a[i][j],a[i][k] + a[k][j]);
		int ans = 0;
		for(int i = 0;i < n;i ++)
		{
			int cur = 0;
			for(int j = 0;j < n;j ++) 
				if (i != j)
					cur = max(cur,a[i][j]);
			if (cur == inf) return -1; //no limit with someone
			ans = max(ans,cur);
		}
		return ans * d;
	}
};
