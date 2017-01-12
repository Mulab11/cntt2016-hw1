#include <bits/stdc++.h>

using namespace std;

const int maxn = 2505,mo = int(1e9) + 7;

int a[maxn][2],fa[maxn],siz[maxn],f[maxn],n;

class GooseInZooDivOne
{
public:
	int get(int a)
	{
		return fa[a] == a ? a : fa[a] = get(fa[a]);
	}

	int count(vector<string> field, int dist)
	{
		for(int i = 0;i < field.size();i ++)
			for(int j = 0;j < field[i].length();j ++)
				if (field[i][j] == 'v') a[n ++][0] = i,a[n - 1][1] = j;
		for(int i = 0;i < n;i ++) fa[i] = i,siz[i] = 1;
		for(int i = 0;i < n;i ++)
			for(int j = i + 1;j < n;j ++)
				if (abs(a[i][0] - a[j][0]) + abs(a[i][1] - a[j][1]) <= dist) //point i and point j should be in a same set
				{
					int u = get(i),v = get(j);
					if (u == v) continue;
					fa[v] = u;
					siz[u] += siz[v];
				}
		f[0] = 1;
		for(int i = 0;i < n;i ++)
			if (fa[i] == i) //the status of all the points in this set should be same,either geese or ducks
				for(int j = n;j >= siz[i];j --)
					f[j] = (f[j] + f[j - siz[i]]) % mo;
		int ans = 0;
		for(int i = 1;i <= n;i ++)
			if (i % 2 == 0) //the number must be even
				ans = (ans + f[i]) % mo;
		return ans;
	}
};
