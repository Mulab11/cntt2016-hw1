#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

const int MAXN = 100 + 10;
const int MAXM = 2 * MAXN * MAXN + 1000;

class PointyWizardHats
{
	public:
	
	struct edge
	{
		int next, to;
	}
	e[MAXM];
	int p[MAXN], l;
	
	void addE(int x, int y)
	{
		e[l].next = p[x];
		e[l].to = y;
		p[x] = l++;
	}
	
	int n, m;
	int match[2][MAXN], vis[MAXN];
	int ans;
	
	bool dfs(int x)
	{
		for(int i = p[x]; i; i = e[i].next)
			if(!vis[e[i].to])
			{
				int y = e[i].to;
				vis[y] = true;
				if(match[1][y] == -1 || dfs(match[1][y]))
				{
					match[1][y] = x, match[0][x] = y;
					return true;
				}
			}
		return false;
	}
	
	void hungary()
	{
		memset(match, -1, sizeof(match));
		for(int i = 1; i <= n; i++)
		{
			memset(vis, 0, sizeof(vis));
			if(dfs(i)) ans++;
		}
	}
	
	int getNumHats(vector<int> topHeight, vector<int> topRadius, vector<int> bottomHeight, vector<int> bottomRadius)
	{
		memset(p, 0, sizeof(p)), l = 2;
		n = topHeight.size();
		m = bottomHeight.size();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				if(topRadius[i] < bottomRadius[j] && topHeight[i] * bottomRadius[j] > bottomHeight[j] * topRadius[i])
					addE(i + 1, j + 1);
		ans = 0;
		hungary();
		
		return ans;
	}
};

