#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
class PolygonTraversal
{
private:
	long long f[1 << 18][18];//f[S][i]: status S, endpoint i, number of ways
	bool intersect(int S, int u, int v) const//if edge u --- v intersects status S
	{
		if(u > v)
			swap(u, v);
		return (S & ((1 << v) - (1 << (u + 1)))) && (~(~S | ((1 << (v + 1)) - (1 << u))));
	}
public:
	long long count(int N, vector<int> points)
	{
		int start = 0;
		for(int i = 0; i < points.size(); i++)
			start |= (1 << (points[i] - 1));
		memset(f, 0, sizeof(f));
		f[start][points.back() - 1] = 1;
		for(int i = ((start + 1) | start); i < (1 << N); i = ((i + 1) | start))//enumerate status
			for(int j = 0; j < N; j++)//enumerate end point
				if(i & (1 << j))
					for(int k = 0; k < N; k++)//enumerate 2nd last point
						if(k != j && (i & (1 << j)) && intersect(i, j, k))//intersect
							f[i][j] += f[i ^ (1 << j)][k];
		long long ans = 0;
		for(int j = 0; j < N; j++)//enumerate final end point
			if(intersect((1 << N) - 1, points[0] - 1, j))
				ans += f[(1 << N) - 1][j];//final status has all of N points
		return ans;
	}
};

