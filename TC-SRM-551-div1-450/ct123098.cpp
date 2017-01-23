#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

const int MAXN = 50 + 10;
const int INF = 0x1f1f1f1f;

class ColorfulWolves
{
	public:
	int n;
	int dis[MAXN][MAXN];
	void floyd()
	{
		for(int k = 0; k < n; k++)
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);		
	}

	int getmin(vector<string> colormap)
	{
		n = colormap.size();
		memset(dis, 31, sizeof(dis));
		for(int i = 0; i < n; i++)
			dis[i][i] = 0;
		for(int i = 0; i < n; i++)
		{
			int tmp = 0;
			for(int j = 0; j < n; j++)
				if(colormap[i][j] == 'Y')
				{
					dis[i][j] = min(dis[i][j], tmp);
					tmp++;
				}
		}
		floyd();

		return dis[0][n - 1] >= INF ? -1 : dis[0][n - 1];
	}
};

