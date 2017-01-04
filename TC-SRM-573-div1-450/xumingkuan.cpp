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
#include <queue>
using namespace std;

class SkiResorts
{
private:
	int n;
	long long f[55][55];//f[i][j]: from 0 to i, change altitude[i] to altitude[j], min cost
	bool inque[55];
	queue<int> q;
public:
	long long minCost(vector<string> road, vector<int> altitude)
	{
		n = road.size();
		memset(inque, false, sizeof(inque));
		q.push(0);
		memset(f, 63, sizeof(f));
		for(int i = 0; i < n; i++)
			f[0][i] = abs(altitude[i] - altitude[0]);
		while(!q.empty())//spfa
		{
			int now = q.front();
			q.pop();
			for(int i = 0; i < n; i++)//from now to i
			{
				if(road[now][i] == 'N')
					continue;
				bool flag = false;
				for(int j = 0; j < n; j++)
				{
					long long tmp = f[i][j], tmp2;
					for(int k = 0; k < n; k++)
						if(altitude[k] >= altitude[j] && (tmp2 = f[now][k] + abs(altitude[i] - altitude[j])) < tmp)
							tmp = tmp2;
					if(tmp < f[i][j])//update
					{
						flag = true;
						f[i][j] = tmp;
					}
				}
				if(flag && !inque[i])
				{
					q.push(i);
					inque[i] = true;
				}
			}
		}
		long long ans = 10101010101010ll;
		for(int i = 0; i < n; i++)
			if(f[n - 1][i] < ans)
				ans = f[n - 1][i];
		return ans == 10101010101010ll ? -1 : ans;
	}
};

