#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;
const int mo = int(1e9) + 9;

bool vis[maxn][maxn];
map<vector<int>,int> sav[maxn];

class Mountains
{
public:
	int hi[maxn],w,n;

	int dfs(int cur,vector<int> h)//cur denotes the id of mountain we are now considering;h denotes the height that has been covered of every column
	{
		if (cur < 0) return 1;//we get a legal solution
		if (sav[cur].find(h) != sav[cur].end()) return (sav[cur].find(h))->second;//memorized
		int tmp = 0;
		for(int i = 0;i < w;i ++)
		{
			bool ok = 1;
			for(int j = 0;j < w;j ++)
			{
				int ch = hi[cur] - abs(i - j);
				if ((h[j] < ch && ch >= 0) != vis[cur][j]) ok = 0;//illegal at column j can be visable != presupposed
			}
			if (ok)
			{
				vector<int> h2 = h;
				for(int j = 0;j < w;j ++)
					h2[j] = max(h2[j],hi[cur] - abs(i - j));
				tmp = (tmp + dfs(cur - 1,h2)) % mo;
			} 
		}
		return sav[cur][h] = tmp;
	}

	int countPlacements(vector<int> heights, vector<string> visibility)
	{
		n = visibility.size();
		w = visibility[0].length();
		for(int i = 0;i < n;i ++) hi[i] = heights[i] - 1;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < w;j ++) vis[i][j] = (visibility[i][j] == 'X');
		vector<int> h;
		h.clear();
		h.resize(w,-1); //initally every column is not covered
		return dfs(n - 1,h);
	}
};
