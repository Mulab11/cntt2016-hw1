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

const int MOD = 1000000009;
const int MAXN = 10 + 5;

class Mountains
{
	public:
	
	int n, m;
	
	map<pair<int, vector<int> >, int> f;
	int hei[MAXN], vis[MAXN][2];
	
	bool check(int pos, int x, const vector<int> &y)
	{
		int l = m - 1, r = 0;
		for(int i = - hei[x] + 1; i <= hei[x] - 1; i++)
			if(0 <= pos + i && pos + i <= m - 1)
				if(hei[x] - abs(i) > y[pos + i])
					l = min(l, pos + i), r = max(r, pos + i);
		return l == vis[x][0] && r == vis[x][1];
	}
	
	int search(int x, const vector<int> &y)
	{
//		cout << "Print : " << x << "  ";
//		for(int i = 0; i < m; i++)
//			cout << y[i] << ' ';
//		cout << endl;
		
		if(x <= 0)
			return 1;
		if(f.find(make_pair(x, y)) != f.end())
			return f[make_pair(x, y)];
		
		int ret = 0;
		if(vis[x - 1][0] == m - 1 && vis[x - 1][1] == 0)
		{
			for(int i = 0; i < m; i++)
				if(hei[x - 1] <= y[i])
					ret++;
			ret = (long long)ret * search(x - 1, y) % MOD;
			return f[make_pair(x, y)] = ret;
		}
		for(int i = 0; i < m; i++)
			if(check(i, x - 1, y))
			{
				vector<int> yy = y;
				for(int j = - hei[x - 1] + 1; j <= hei[x - 1] - 1; j++)
					if(0 <= i + j && i + j <= m - 1)
						yy[i + j] = max(yy[i + j], hei[x - 1] - abs(j));
				ret = (ret + search(x - 1, yy)) % MOD;
			}
		return f[make_pair(x, y)] = ret;
	}
	
	int countPlacements(vector<int> heights, vector<string> visibility)
	{
		n = heights.size();
		m = visibility[0].size();
		for(int i = 0; i < n; i++)
			hei[i] = heights[i];
		for(int i = 0; i < n; i++)
		{
			vis[i][0] = m - 1, vis[i][1] = 0;
			for(int j = 0; j < m; j++)
				if(visibility[i][j] == 'X')
					vis[i][0] = min(vis[i][0], j), vis[i][1] = max(vis[i][1], j);
		}
		
		f.clear();
		int ans = search(n, vector<int>(m));
		
		return ans;
	}
};

