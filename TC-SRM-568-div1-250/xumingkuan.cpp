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
using namespace std;
class BallsSeparating
{
	private:
	int n;//number of boxes
	bool have[3];//if there is at least 1 red/green/blue ball
	int cost[60][3], mincost[60];//cost[i][j] = cost of changing box i to color j, mincost[i] = min(cost[i][j])
	bool used[60];
	int search(int numColor)//calculate the cost of that there must be at least 1 box for each color. O(n^3)
	{
		if(numColor == 3)
			return 0;
		if(!have[numColor])
			return search(numColor + 1);
		int ret = 1010101010;
		for(int i = 0; i < n; i++)
			if(!used[i])
			{
				used[i] = true;//choose box i for color numColor
				ret = min(ret, search(numColor + 1) + cost[i][numColor] - mincost[i]);
				used[i] = false;
			}
		return ret;
	}
	public:
	int minOperations(vector<int> red, vector<int> green, vector<int> blue)
	{
		for(int i = 0; i < 3; i++)
			have[i] = false;
		n = red.size();
		int ans = 0;
		for(int i = 0; i < red.size(); i++)
		{
			int tmp[3] = {red[i], green[i], blue[i]};
			for(int j = 0; j < 3; j++)
			{
				if(tmp[j])
					have[j] = true;//in fact it's guaranteed that there is at least 1 ball for each of 3 colors... so the code can be greatly simplified...
				if((cost[i][j] = tmp[(j + 1) % 3] + tmp[(j + 2) % 3]) < mincost[i] || !j)//e.g. the cost of changing box i to red is (green + blue)
					mincost[i] = cost[i][j];
			}
			ans += mincost[i];
		}
		memset(used, false, sizeof(used));
		ans += search(0);
		return ans >= 1010101010 ? -1 : ans;//>= 1010101010 if there isn't enough boxes
	}
};

