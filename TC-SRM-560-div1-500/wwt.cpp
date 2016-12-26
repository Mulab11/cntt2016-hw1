/*
先把所有点的坐标都*2，二分答案。可以发现，对于一个最终在(x,y)的点，要在k步后能搞到(x,y)，那么他周围必然有一个2k*2k的点阵(每次x+2,y+2这样)，
那么直接把一开始所有的点都搞出来，然后模拟一遍就好了。可以发现，答案最多不会超过|x|+|y|=140（否则显然会搞出来一些新点）
*/
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pi;

const int xy[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};

class DrawingPointsDivOne
{
public:

	int vis[2005][2005],tag;
	set<pi> a;
	vector<pi> b,c;

	bool test(int step)
	{
		b.clear();
		tag ++;
		//搞出周围的点阵
		for(auto p = a.begin();p != a.end();p ++)
		{
			int x = p->first,y = p->second;
			for(int lx = x - step;lx <= x + step;lx += 2)
				for(int ly = y - step;ly <= y + step;ly += 2)
				{
					if (vis[lx + 1000][ly + 1000] != tag)
						b.push_back(pi(lx,ly)),vis[lx + 1000][ly + 1000] = tag;
				}
		}
		//模拟过程
		for(;step;step --)
		{
			c.clear();
			for(auto p = b.begin();p != b.end();p ++)
			{
				int x = p->first,y = p->second;
				bool ok = 1;
				for(int i = 0;i < 2;i ++)
					for(int j = 0;j < 2;j ++)
						if (vis[x + i * 2 + 1000][y + j * 2 + 1000] != tag) {ok = 0;break;}
				if (ok)
				{
					if (vis[x + 1001][y + 1001] != tag + 1) 
						c.push_back(pi(x + 1,y + 1)),vis[x + 1 + 1000][y + 1 + 1000] = tag + 1;
				}
			}
			++ tag;
			swap(b,c);
		}
		if (b.size() != a.size()) return 0;
		for(auto p = b.begin();p != b.end();p ++)
			if (a.find(*p) == a.end()) return 0;
		return 1;
	}

	int maxSteps(vector<int> x, vector<int> y)
	{
		a.clear();
		memset(vis,0,sizeof vis);
		for(int i = 0;i < x.size();i ++)
			a.insert(pi(x[i] * 2,y[i] * 2));
		int l = 0,r = 141,tmp = 0;
		for(int mid;l <= r;)
		{
			mid = l + r >> 1;
			if (test(mid)) tmp = mid,l = mid + 1; else r = mid - 1;
		}
		if (tmp > 140) tmp = -1;
		return tmp;
	}
};
