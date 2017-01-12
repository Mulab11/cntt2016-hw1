#include <bits/stdc++.h>

using namespace std;

class NewArenaPassword
{
public:
	int fa[55];

	int get(int a)
	{
		return fa[a] == a ? a : fa[a] = get(fa[a]);
	}

	int minChange(string oldPassword, int K)
	{
		static int co[55][30],siz[55];
		memset(co,0,sizeof co);
		int n = oldPassword.size();
		for(int i = 0;i < n;i ++)
			fa[i] = i,siz[i] = 0;
		for(int i = 0;i < K;i ++)
		{
			int u = i,v = n - K + i;
			u = get(u),v = get(v);
			fa[u] = v; //the positions that have to have the same char will be in a same set
		}
		for(int i = 0;i < n;i ++)
		{
			int u = get(i);
			siz[u] ++,co[u][oldPassword[i] - 'a'] ++; //for every set,calculate the frequency of every char
		}
		int ans = 0;
		for(int i = 0;i < n;i ++)
			if (fa[i] == i)
			{
				int mx = 0;
				for(int ch = 0;ch < 26;ch ++) mx = max(mx,co[i][ch]); //greedy,choose the best char to be
				ans += siz[i] - mx;
			}
		return ans;
	}
};
