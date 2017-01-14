#include <bits/stdc++.h>

using namespace std;

class TravelOnMars
{
public:
	int n;

	int dis(int a,int b)
	{
		if (a > b) swap(a,b);
		return min(b - a,n - (b - a));
	}

	int minTimes(vector <int> range, int startCity, int endCity)
	{
		n = range.size();
		static int d[55];
		static int que[55];
		memset(d,255,sizeof d);
		d[startCity] = 0;
		que[1] = startCity;
		for(int fi = 1,en = 1;fi <= en;fi ++) //bfs
		{
			int u = que[fi];
			for(int i = 0;i < range.size();i ++) //enumerate the next city to go
				if (dis(u,i) <= range[u])
				{
					if (d[i] == -1) d[i] = d[u] + 1,que[++ en] = i;
				}
		}
		return d[endCity];
	}
};
