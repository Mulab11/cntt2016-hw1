#include <algorithm>
using namespace std;
const int inf = 1000000000;
class TravellingPurchasingMan
{
public:
	int m, l[20], r[20], t[20], dis[50][50], f[1 << 16][16];
	vector<int> Parse(string str)
	{
		vector<int> ret;
		ret.push_back(0);
		for(int i = 0, j = 0; i < str.length(); i++)
		{
			if(str[i] == ' ')
				ret.push_back(0), j++;
			else
				ret[j] = ret[j] * 10 + (str[i] - '0');
		}
		return ret;
	}
	int maxStores(int n, vector<string> store, vector<string> roads)
	{
		m = store.size();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				dis[i][j] = inf;
			dis[i][i] = 0;
		}
		for(int i = 0; i < m; i++)
		{
			vector<int> vec = Parse(store[i]);
			l[i] = vec[0], r[i] = vec[1], t[i] = vec[2];
		}
		for(int i = 0; i < roads.size(); i++)
		{
			vector<int> vec = Parse(roads[i]);
			int u = vec[0], v = vec[1], w = vec[2];
			dis[u][v] = min(dis[u][v], w);
			dis[v][u] = min(dis[v][u], w);
		}
		for(int k = 0; k < n; k++)
		{
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
		int ans = 0;
		for(int i = 0; i < 1 << m; i++) 
		{
			int cnt = 0;
			for(int j = 0; j < m; j++)
				cnt += (i >> j) & 1;
			for(int j = 0; j < m; j++) //求出在当前商店完成购买的最小时间 
			{
				f[i][j] = inf;
				if(!((i >> j) & 1))
					continue;
				if(i == 1 << j) 
					f[i][j] = dis[n - 1][j];
				else
				{
					for(int k = 0; k < m; k++)
					{
						if((i >> k) & 1 && k != j)
							f[i][j] = min(f[i][j], f[i - (1 << j)][k] + dis[k][j]);
					}
				}
				if(f[i][j] <= r[j]) //可以在关闭前到达，并更新答案 
					f[i][j] = max(f[i][j], l[j]) + t[j], ans = max(ans, cnt);
				else //商店已经关闭 
					f[i][j] = inf;
			}
		}
		return ans;
	}
};