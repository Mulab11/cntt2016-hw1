#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <queue>
#include <map>
#include <set>
using namespace std;

class TravelOnMars
{
private:
	int n;
	int dist[55];//min dist from startCity
	int a[55];//range
	void update(int x)
	{
		for(int i = 1; i <= a[x]; i++)
		{
			dist[(x + i) % n] = min(dist[(x + i) % n], dist[x] + 1);
			dist[(x - i + n) % n] = min(dist[(x - i + n) % n], dist[x] + 1);
		}
	}
public:
	int minTimes(vector<int> range, int startCity, int endCity)
	{
		n = range.size();
		for(int i = 0; i < n; i++)
			a[i] = min(range[i], n / 2);
		memset(dist, 31, sizeof(dist));
		dist[startCity] = 0;
		update(startCity);
		int le = (startCity - 1 + n) % n, ri = (startCity + 1) % n;
		while(le != ri)//dijkstra, O(n^2) (O(1) find the minimal dist with 2 pointers)
		{
			if(dist[le] < dist[ri])
			{
				update(le);
				le = (le - 1 + n) % n;
			}
			else
			{
				update(ri);
				ri = (ri + 1) % n;
			}
		}
		return dist[endCity];
	}
};

