#include <bits/stdc++.h>

using namespace std;

class PolygonTraversal
{
public:
	long long f[25][1 << 18]; //memorized
	vector<int> p;
	int n;

	bool legal(int u,int v,int s)
	{
		if (u > v) swap(u,v); //keep them ordered
		//the order of the appeared points is not important,we just need to assure that u,v will cross any of the segments which may appear
		bool exist_left = 0,exist_right = 0;
		for(int i = 0;i < n;i ++)
			if (s & (1 << i))
			{
				exist_left |= !(u <= i && i <= v);
				exist_right |= (u < i && i < v);
			}
		return exist_left && exist_right;
	}

	long long dfs(int lst,int s) //current point, the points that have been chosen
	{
		if (~f[lst][s]) return f[lst][s];
		if (s == (1 << n) - 1) //has chosen every point
			return legal(lst,p[0] - 1,s); //every segment must be legal
		long long tmp = 0;
		for(int nxt = 0;nxt < n;nxt ++) 
			if (!(s & (1 << nxt)) && legal(lst,nxt,s))
				tmp = tmp + dfs(nxt,s | (1 << nxt));
		return f[lst][s] = tmp; 
	}

	long long count(int N,vector<int> points)
	{
		memset(f,255,sizeof f);
		p = points;
		n = N;
		int s = 0;
		for(auto p : points) s |= (1 << (p - 1));
		return dfs(points[points.size() - 1] - 1,s);
	}
};
