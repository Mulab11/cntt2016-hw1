#include <algorithm>
#include <memory.h>
using namespace std;
const int inf = 1000000000;
class OldBridges
{
public:
	int n, s, t, flow[52][52], level[52], que[52];
	bool MakeLevel()
	{
		que[0] = s;
		for(int i = 0; i <= t; i++)
			level[i] = -1;
		level[s] = 0;
		for(int l = 0, r = 1; l < r; l++)
		{
			int cur = que[l];
			for(int i = 0; i <= t; i++)
			{
				if(flow[cur][i] && level[i] < 0)
					level[i] = level[cur] + 1, que[r++] = i;
			}
		}
		return level[t] >= 0;
	}
	int Dfs(int cur, int mf)
	{
		if(cur == t)
			return mf;
		int ret = 0;
		for(int i = 0; i <= t && mf; i++)
		{
			if(level[cur] + 1 == level[i] && flow[cur][i])
			{
				int f = Dfs(i, min(mf, flow[cur][i]));
				ret += f;
				mf -= f;
				flow[cur][i] -= f;
				flow[i][cur] += f;
			}
		}
		if(!ret)
			level[cur] = -1;
		return ret;
	}
	int Flow()
	{
		int ans = 0;
		while(MakeLevel())
			ans += Dfs(s, inf);
		return ans;
	}
	string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn)
	{
		n = bridges.size();
		s = n, t = n + 1;
		memset(flow, 0, sizeof(flow));
		for(int i = 0; i < n; i++) //建图 
		{
			for(int j = 0; j < n; j++)
				flow[i][j] = bridges[i][j] == 'O' ? 2 : bridges[i][j] == 'N' ? inf : 0;
		}
		flow[s][a1] = flow[a2][t] = an * 2;
		flow[s][b1] = flow[b2][t] = bn * 2;
		if(Flow() < an * 2 + bn * 2)
			return "No";
		memset(flow, 0, sizeof(flow)); //反转再跑一次网络流 
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				flow[i][j] = bridges[i][j] == 'O' ? 2 : bridges[i][j] == 'N' ? inf : 0;
		}
		flow[s][a1] = flow[a2][t] = an * 2;
		flow[s][b2] = flow[b1][t] = bn * 2;
		if(Flow() < an * 2 + bn * 2)
			return "No";
		return "Yes";
	}
};