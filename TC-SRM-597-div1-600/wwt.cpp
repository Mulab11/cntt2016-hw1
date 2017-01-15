#include <bits/stdc++.h>
#define fe first
#define se second

using namespace std;

const int inf = 100000;

class ConvexPolygonGame
{
public:
	bool line(pair<int,int> a,pair<int,int> b,pair<int,int> c)
	{
		return (b.fe - a.fe) * 1ll * (c.se - a.se) == (b.se - a.se) * 1ll * (c.fe - a.fe);
	}

	string winner(vector<int> X,vector<int> Y)
	{
		vector< pair<int,int> > ava;//valid points
		ava.clear();
		for(int x = -inf;x <= inf;x ++)
		{
			bool cross = 0;
			int miny = -inf,maxy = inf;
			for(int i = 0;i < X.size();i ++)
			{
				int cx = X[i],cy = Y[i],nx = X[(i + 1) % X.size()],ny = Y[(i + 1) % Y.size()];
				if (x < min(cx,nx) || x > max(cx,nx)) continue;
				cross = 1;
				if (cx == nx) 
					miny = min(cy,ny) + 1,maxy = max(cy,ny) - 1; else
				{
					if (cx < nx) //update miny
					{
						double y = ceil((ny - cy) / 1.0 / (nx - cx) * (x - cx) + cy);
						if (y == cy && x == cx || y == ny && x == nx) y ++; //no point coincides
						miny = max(miny,int(y));
					} else //updaet maxy
					{
						double y = floor((ny - cy) / 1.0 / (nx - cx) * (x - cx) + cy);
						if (y == cy && x == cx || y == ny && x == nx) y --;
						maxy = min(maxy,int(y));
					}
				}
			}
			if (!cross) continue; //out of the polygon
			for(;miny <= maxy;miny ++)
			{
				ava.push_back(make_pair(x,miny));
				if (ava.size() > 2 * inf) //a line in squares with side length = inf can include at most inf points
					return "Masha";
			}
		}
		for(int i = 2;i < ava.size();i ++)
			if (!line(ava[0],ava[1],ava[i])) return "Masha";//we only need to make a triangle to win
		return "Petya";
	}
};
