#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

class HatRack
{
public:
	int co[maxn];
	int n,final[maxn],to[maxn * 2],nex[maxn * 2],tot,max_dep;
	long long f[maxn][3][3];
	bool lev[maxn],ok;

	void link(int u,int v)
	{
		to[++ tot] = v,nex[tot] = final[u],final[u] = tot;
	}

	void get_max_dep(int now,int pre,int dep)
	{
		max_dep = max(max_dep,dep);
		co[dep] ++;
		for(int i = final[now];i;i = nex[i])
			if (to[i] != pre) get_max_dep(to[i],now,dep + 1);
	}	
	//枚举根，dp,设f[u][l][r]表示u这棵子树开头为状态l，结尾为状态r，直接合并就好了。
	void dfs(int now,int pre,int dep)
	{
		if (dep == max_dep) return;
		static int ch[20];
		int co = 0;
		memset(f[now],0,sizeof f[now]),memset(ch,0,sizeof ch);
		for(int i = final[now];i;i = nex[i])
			if (to[i] != pre) ch[++ co] = to[i];
		if (co > 2) ok = 0; else
		{
			int l = ch[1],r = ch[2];
			if (!l)
			{
				if (dep < max_dep - 1) ok = 0; else f[now][0][0] = 1;
			} else
			{
				if (!r)
				{
					if (dep < max_dep - 1) ok = 0; else f[now][1][1] = 1;
				} else
				{
					if (dep < max_dep - 1)
					{
						dfs(l,now,dep + 1),dfs(r,now,dep + 1);
						for(int x = 2;x >= 0;x --)
							for(int y = x;y >= 0;y --)
								for(int x1 = y == 2 ? 2 : 0;x1 >= 0;x1 --)
									for(int y1 = x1;y1 >= 0;y1 --)
										f[now][x][y1] += f[l][x][y] * f[r][x1][y1] + f[r][x][y] * f[l][x1][y1]; //顺序可以交换
					} else f[now][2][2] = 2;
				}
			}
		}
	}

	long long countWays(vector <int> knob1, vector <int> knob2)
	{
		n = knob2.size() + 1;
		memset(final,0,sizeof final);
		tot = 0;
		for(int i = 0;i < n - 1;i ++)
			link(knob1[i],knob2[i]),link(knob2[i],knob1[i]);
		long long ans = 0;
		for(int u = 1;u <= n;u ++)
		{
			memset(co,0,sizeof co);memset(lev,0,sizeof lev);
			ok = 1;
			max_dep = 0;
			get_max_dep(u,0,0); //找到最大的深度
			dfs(u,0,0);
			for(int i = 0;i < max_dep;i ++)
				if (co[i] && co[i] != (1ll << i)) {ok = 0;break;} //除了最底下一层外其他都要填满
			if (ok)
			{
				for(int x = 2;x >= 0;x --)
					for(int y = x;y >= 0;y --)
						ans += f[u][x][y];
			}
		}
		return ans;
	}
};
