#include <algorithm>
using namespace std;
const long long inf = 0x7FFFFFFFFFFFFFFFLL;
class SkiResorts
{
public:
	bool vis[50][50];
	long long dis[50][50];
	pair<int, int> que[6250000];
	long long minCost(vector<string> road, vector<int> h)
	{
		int n = road.size();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				dis[i][j] = inf;
		}
		int l = 0, r = 1;
		for(int i = 0; i < n; i++)
		{
			if(h[i] >= h[0]) //可以提升起点的高度 
			{
				dis[0][i] = h[i] - h[0];
				vis[0][i] = true;
				que[r++] = make_pair(0, i);
			}
		}
		for(; l < r; l++)
		{
			int p = que[l].first, q = que[l].second;
			for(int i = 0; i < n; i++) //以当前高度往后走 
			{
				if(road[p][i] == 'Y')
				{
					for(int j = 0; j < n; j++)
					{
						if(h[j] > h[q])
							continue;
						int w = abs(h[i] - h[j]); //修改目标点高度 
						if(dis[p][q] + w < dis[i][j])
						{
							dis[i][j] = dis[p][q] + w;
							if(!vis[i][j])
								vis[i][j] = true, que[r++] = make_pair(i, j);
						}
					}
				}
			}
			vis[p][q] = false;
		}
		long long ans = inf;
		for(int i = 0; i < n; i++)
			ans = min(ans, dis[n - 1][i]);
		return ans < inf ? ans : -1;
	}
};