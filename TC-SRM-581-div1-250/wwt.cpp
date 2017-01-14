#include <bits/stdc++.h>

using namespace std;


class SurveillanceSystem
{
public:
	vector<int> r;
	bool ok[55];
	int n,m,m1,lx[55],vis[55],co[55];

	int dfs(int now)
	{
		for(int j = 0;j < m1;j ++)
			if (!vis[j] && r[now] == co[j] && ok[j])
			{
				vis[j] = 1;
				if (lx[j] == -1 || dfs(lx[j])) 
					return lx[j] = now,1;
			}
		return 0;
	}

	int max_match()
	{
		memset(lx,255,sizeof lx);
		int tmp = 0;
		for(int i = 0;i < m;i ++)
		{
			memset(vis,0,sizeof vis);
			tmp += dfs(i);
		}
		return tmp;
	}

	string getContainerInfo(string containers,vector<int> reports, int L)
	{
		n = containers.length(),m = reports.size(),m1 = n - L + 1;
		r = reports;
		for(int i = 0;i <= n - L;i ++)
		{
			co[i] = 0; //the number of containers that the segment [i,i+L) has
			for(int j = 0;j < L;j ++) 
				co[i] += (containers[i + j] == 'X');
		}
		for(int i = 0;i <= n - L;i ++) ok[i] = 1; //if i can choose
		string ans = "";
		for(int i = 0;i < n;i ++)
		{
			//delete all the segments that cover i
			for(int j = max(0,i - L + 1);j <= i;j ++) ok[j] = 0;
			if (max_match() != m) ans = ans + '+'; else//we must cover i
			{
				bool not_cover = 1;
				for(int j = max(0,i - L + 1);j <= i && j + L - 1 < n;j ++)
					for(int k = 0;k < m;k ++)
						if (reports[k] == co[j]) not_cover = 0;//possiblily covered
				if (not_cover) ans = ans + '-'; else ans = ans + '?';
			}
			for(int j = max(0,i - L + 1);j <= i;j ++) ok[j] = 1;
		}
		return ans;
	}
};
