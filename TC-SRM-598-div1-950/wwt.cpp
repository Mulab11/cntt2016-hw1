#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

vector<int> lk[maxn];
int f[maxn][maxn][2],n;

class TPS
{
public:
	int dfs(int now,int pre,bool must) //当前考虑的子树，以及这棵子树是否必须放东西
	{
		int &tmp = f[now][pre][must];
		if (~tmp) return tmp;
		int sum = 0,co = 0;//sum = \sum_{p is now's child} f(p,1),co:儿子个数
		for(auto p : lk[now])
			if (p != pre) sum += dfs(p,now,1),++ co;
		if (!co)//是个叶子
		{
			if (must) return tmp = 1; //必须放
			return tmp = 0;
		}
		int els = n;
		for(auto p : lk[now])
			if (p != pre) els = min(els,sum - dfs(p,now,1) + dfs(p,now,0)); //正常来讲允许有一棵子树不放
		tmp = 1 + els;//根放东西
		if (pre != n)//深度最小的点必须放（Dp基础）
		{
			if (must && co == 1) tmp = min(tmp,sum); else //假如必须放东西，而只有一个儿子，那么这个儿子是必须放的
				tmp = min(tmp,els);
		}
		return tmp;
	}

	int minimalBeacons(vector<string> linked)
	{
		n = linked.size();
		if (n == 1) return 0;
		for(int i = 0;i < linked.size();i ++)
			for(int j = 0;j < linked[0].length();j ++)
				if (linked[i][j] == 'Y')
					lk[i].push_back(j);
		int ans = n;
		memset(f,255,sizeof f);
		for(int i = 0;i < n;i ++)
			ans = min(ans,dfs(i,n,0));
		return ans;
	}
};
