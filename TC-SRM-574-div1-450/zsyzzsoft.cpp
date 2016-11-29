#include <vector>
using namespace std;
long long dp[1 << 18][18], ans;
bool visit[18];
class PolygonTraversal
{
public:
	long long count(int n, vector<int> points)
	{
		for(int i = 0; i < points.size(); i++)
			visit[points[i] - 1] = true;
		for(int i = 0; i < 1 << n; i++) //状压dp 
		{
			for(int j = 0; j < n; j++)
			{
				if(!((i >> j) & 1))
					continue;
				bool flag = false;
				int cnt = 0;
				for(int k = 0; k < n && !flag; k++)
				{
					if((i >> k) & 1)
						cnt++;
					if(visit[k] && !((i >> k) & 1))
						flag = true;
				}
				if(flag)
					continue;
				if(cnt == points.size())
				{
					if(j == points[points.size() - 1] - 1)
						dp[i][j] = 1;
					continue;
				}
				if(cnt <= 3)
					continue;
				int l = (j + n - 1) % n, r = (j + 1) % n;
				while(!((i >> l) & 1))
					l = (l + n - 1) % n;
				while(!((i >> r) & 1))
					r = (r + 1) % n;
				for(int k = (r + 1) % n; k != l; k = (k + 1) % n)
				{
					if((!visit[k] || cnt == points.size() + 1) && (i >> k) & 1)
						dp[i][j] += dp[i ^ (1 << j)][k];
				}
			}
		}
		for(int k = 0; k < n; k++)
		{
			if(!visit[k] && k != (points[0] + n - 2) % n && k != (points[0]) % n)
				ans += dp[(1 << n) - 1][k];
		}
		return ans;
	}
};