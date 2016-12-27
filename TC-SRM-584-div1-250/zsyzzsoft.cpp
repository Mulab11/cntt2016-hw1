#include <algorithm>
using namespace std;
const int inf = 1000000000;
class Egalitarianism
{
public:
	int dis[50][50];
	int maxDifference(vector<string> graph, int d)
	{
		int n = graph.size();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				dis[i][j] = graph[i][j] == 'Y' ? 1 : inf;
			dis[i][i] = 0;
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
		for(int i = 0; i < n; i++) //答案受最长的最短路制约 
		{
			for(int j = 0; j < n; j++)
				ans = max(ans, dis[i][j]);
		}
		return ans < inf ? ans * d : -1;
	}
};