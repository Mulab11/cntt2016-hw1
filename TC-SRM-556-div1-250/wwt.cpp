/*
直接设f[u][v]表示到点u权值为v是否可行，记忆化即可。
*/
#include <bits/stdc++.h>

using namespace std;

class XorTravelingSalesman
{
public:
	vector<int> lk[55],v;
	bool f[55][2005];

	void dfs(int now,int val)
	{
		if (f[now][val]) return;
		f[now][val] = 1;
		for(int i = 0;i < lk[now].size();i ++) //go
			dfs(lk[now][i],val ^ v[lk[now][i]]);
	}

	int maxProfit(vector <int> cityValues, vector <string> roads)
	{
		v = cityValues;
		int n = cityValues.size();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < n;j ++)
				if (roads[i][j] == 'Y') lk[i].push_back(j);
		dfs(0,v[0]);
		int ans = 0;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < 2000;j ++)
				if (f[i][j]) ans = max(ans,j);
		return ans;
	}
};
