#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

typedef long double ld;

class CandyOnDisk
{
public:
	map<pair<int,int>,int> sav;

	bool intersect(ld l,ld r,ld i,ld j)
	{
		if (l > r || i > j || i > r || j < l) return 0;
		return 1;
	}

	ld get_dis(ld x,ld y,ld a,ld b)
	{
		auto sqr = [](ld a){return a * a;};
		return sqrtl(sqr(x - a) + sqr(y - b));
	}

	bool work(vector<int> x,vector<int> y,vector<int> r,int sx,int sy,int tx,int ty)
	{
		if (sx == tx && sy == ty) return 1; //we have to specify this situation
		static ld low[maxn],up[maxn];//the upper radius and the lower radius that the points in the area could be reached
		int n = x.size();
		for(int i = 0;i < n;i ++) low[i] = (1e9),up[i] = -(1e9);
		for(int i = 0;i < n;i ++)
		{
			ld dis = get_dis(x[i],y[i],sx,sy);
			if (dis <= r[i]) low[i] = up[i] = dis;
		}
		static bool vis[maxn][maxn];// for every pair of circles we will only update them for once
		for(;;) //expand the reachable area
		{
			bool expand = 0;
			for(int i = 0;i < n;i ++)
				for(int j = 0;j < n;j ++)
					if (i != j && !vis[i][j])
					{
						ld dis = get_dis(x[i],y[i],x[j],y[j]);
						if (intersect(low[i],up[i],dis - r[j],dis + r[j])) //we can expand the area in circle i and circle j
						{
							vis[i][j] = 1;
							low[i] = min(low[i],max(ld(0),dis - r[j]));
							low[j] = min(low[j],max(ld(0),dis - r[i]));
							up[i] = max(up[i],min(dis + r[j],ld(r[i])));
							up[j] = max(up[j],min(dis + r[i],ld(r[j])));
							expand = 1;
						}
					}
			if (!expand) break;
		}
		for(int i = 0;i < n;i ++) //check whether (tx,ty) is in the reachable area of any circle
		{
			ld dis = get_dis(x[i],y[i],tx,ty);
			if (intersect(dis,dis,low[i],up[i])) return 1;
		}
		return 0;
	}

	string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty)
	{
		sav.clear();
		int n = x.size();
		for(int i = 0;i < n;i ++) //if there are multiple circles with the same center,we only save the one with biggest ridius
		{
			pair<int,int> cr = {x[i],y[i]};
			if (!sav[cr]) sav[cr] = r[i]; else
				sav[cr] = max(int(sav[cr]),r[i]);
		}
		x.clear(),y.clear(),r.clear();
		for(auto p:sav)
			x.push_back(p.first.first),y.push_back(p.first.second),r.push_back(p.second);
		return work(x,y,r,sx,sy,tx,ty) ? "YES" : "NO";
	}
};
