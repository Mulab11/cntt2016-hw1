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
		dis[0][0] = 0;
		vis[0][0] = true;
		for(int l = 0, r = 1; l < r; l++)
		{
			int p = que[l].first, q = que[l].second;
			for(int i = 0; i < n; i++)
			{
				if(h[i] > h[q] && dis[p][q] + h[i] - h[q] < dis[p][i])
				{
					dis[p][i] = dis[p][q] + h[i] - h[q];
					if(!vis[p][i])
						vis[p][i] = true, que[r++] = make_pair(p, i);
				}
			}
			for(int i = 0; i < n; i++)
			{
				if(road[p][i] == 'Y')
				{
					int nq = h[q] < h[i] ? q : i, nw = h[i] - h[nq];
					if(dis[p][q] + nw < dis[i][nq])
					{
						dis[i][nq] = dis[p][q] + nw;
						if(!vis[i][nq])
							vis[i][nq] = true, que[r++] = make_pair(i, nq);
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