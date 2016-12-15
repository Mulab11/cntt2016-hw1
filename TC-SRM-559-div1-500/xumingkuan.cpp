#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;

class HatRack
{
	private:
	int n;
	vector <int> to[60];//edges
	long long f[60];//f[i][j]: subtree i, number of ways
	int sum[60];//size of subtree
	bool visit[60];
	bool full[60];//full binary tree
	void dfs(int p)
	{
		visit[p] = true;
		sum[p] = 1;
		int son[2], numSon = 0;
		for(int i = 0; i < to[p].size(); i++)
			if(!visit[to[p][i]])
			{
				dfs(to[p][i]);
				if(!f[to[p][i]])//impossible
					return;
				son[numSon++] = to[p][i];
				sum[p] += sum[to[p][i]];
			}
		if(numSon == 0)//leaf
		{
			f[p] = 1;
			full[p] = true;
			return;
		}
		if(numSon == 1)
		{
			f[p] = (sum[son[0]] == 1);
			return;
		}
		//numSon == 2
		if(full[son[0]] && full[son[1]] && sum[son[0]] == sum[son[1]])
		{
			f[p] = f[son[0]] * f[son[1]] * 2;
			full[p] = true;
			return;
		}
		if(!full[son[0]] && !full[son[1]])
			return;
		if(sum[son[0]] < sum[son[1]])
			swap(son[0], son[1]);
		//put son[0] to the left
		if((full[son[1]] && sum[son[0]] <= sum[son[1]] * 2 + 1) || (full[son[0]] && sum[son[1]] >= sum[son[0]] / 2))
			f[p] = f[son[0]] * f[son[1]];
	}
	public:
	long long countWays(vector<int> knob1, vector<int> knob2)
	{
		n = knob1.size() + 1;
		for(int i = 1; i <= n; i++)
			to[i].clear();
		for(int i = 0; i < n - 1; i++)
		{
			to[knob1[i]].push_back(knob2[i]);
			to[knob2[i]].push_back(knob1[i]);
		}
		for(int i = 1; i <= n; i++)
			if(to[i].size() > 3)//impossible
				return 0;
		long long ans = 0;
		for(int i = 1; i <= n; i++)//enumerate root
			if(to[i].size() <= 2)//root has <= 2 sons
			{
				memset(f, 0, sizeof(f));
				memset(visit, false, sizeof(visit));
				memset(full, false, sizeof(full));
				dfs(i);
				ans += f[i];
			}
		return ans;
	}
};

