#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
#include <bitset>
using namespace std;

class XorTravelingSalesman
{
	private:
	queue <int> q;
	bool visit[60];
	int n, a[60];
	public:
	int maxProfit(vector<int> cityValues, vector<string> roads)
	{
		n = cityValues.size();
		memset(visit, false, sizeof(visit));
		q.push(0);
		visit[0] = true;
		while(!q.empty())//bfs
		{
			int now = q.front();
			q.pop();
			for(int i = 0; i < n; i++)
				if(roads[now][i] == 'Y' && !visit[i])
				{
					visit[i] = true;
					q.push(i);
				}
		}
		for(int i = 0; i < n; i++)
			if(!visit[i])//can't reach i
				a[i] = 0;
			else
				a[i] = cityValues[i];
		int ans = 0;
		for(int i = 10; i >= 0; i--)//get max xor sum
		{
			int val = -1;
			for(int j = 0; j < n; j++)
				if(a[j] & (1 << i))
				{
					val = a[j];
					break;
				}
			if(val == -1)
				continue;
			if(!(ans & (1 << i)))
				ans ^= val;
			for(int j = 0; j < n; j++)
				if(a[j] & (1 << i))
					a[j] ^= val;
		}
		return ans;
	}
};

