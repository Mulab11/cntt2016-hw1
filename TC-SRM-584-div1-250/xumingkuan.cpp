#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;

class Egalitarianism
{
private:
	int n;
	int dist[55][55];//dist[i][j]: greatest possible money difference between i and j
public:
	int maxDifference(vector<string> isFriend, int d)
	{
		memset(dist, 63, sizeof(dist));
		n = isFriend.size();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if(isFriend[i][j] == 'Y')
					dist[i][j] = 1;
		for(int i = 0; i < n; i++)
			dist[i][i] = 0;
		for(int k = 0; k < n; k++)//floyd
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					if(dist[i][k] + dist[k][j] < dist[i][j])
						dist[i][j] = dist[i][k] + dist[k][j];
		int ans = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if(dist[i][j] > ans)
					ans = dist[i][j];
		return ans > 10101010 ? -1 : ans * d;
	}
};

