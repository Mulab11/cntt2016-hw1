#include <bits/stdc++.h>

using namespace std;

class MagicMolecule
{
public:
	bool use[55];
	int n,ans;
	int e[55 * 55][2],cnt;
	vector<int> a;

	void dfs(int now,int lst)
	{
		if (now > cnt)
		{
			int cur = 0;
			for(int i = 0;i < n;i ++)
				if (use[i]) cur += a[i];
			ans = max(ans,cur);
			return;
		}
		if (!use[e[now][0]] || !use[e[now][1]]) {dfs(now + 1,lst);return;} //no use to choose another point 
		if (!lst) return;
		for(int i = 0;i < 2;i ++)
			if (use[e[now][i]])
			{
				use[e[now][i]] = 0;
				dfs(now + 1,lst - 1);
				use[e[now][i]] = 1;
			}
	}

	int maxMagicPower(vector<int> magicPower,vector<string> magicBond)
	{
		memset(use,1,sizeof use);
		n = magicPower.size();
		a = magicPower;
		ans = -1;
		for(int i = 0;i < n;i ++)
			for(int j = i + 1;j < n;j ++)
				if (magicBond[i][j] == 'N') e[++ cnt][0] = i,e[cnt][1] = j;//consider the complement of a graph
		int m;
		for(m = 1;3 * m < 2 * n;m ++);
		dfs(1,n - m);//we can only choose at most n - m points in the complement of a graph,and we need to do a minimum vertexs cover
		return ans;
	}
};
