#include <algorithm>
using namespace std;
int ans, vis[50][1024];
pair<int, int> que[50 << 10];
class XorTravelingSalesman
{
public:
	int n;
	int maxProfit(vector<int> w, vector<string> e)
	{
		n = e.size();
		vis[0][w[0]] = true;
		que[0] = make_pair(0, w[0]);
		for(int l = 0, r = 1; l < r; l++) //Bfs
		{
			int cv = que[l].first, cw = que[l].second;
			ans = max(ans, cw);
			for(int i = 0; i < n; i++)
			{
				if(e[cv][i] == 'Y' && !vis[i][cw ^ w[i]])
				{
					que[r++] = make_pair(i, cw ^ w[i]);
					vis[i][cw ^ w[i]] = true;
				}
			}
		}
		return ans;
	};
};
