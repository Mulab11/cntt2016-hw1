#include <algorithm>
using namespace std;
const int p = 1000000009;
int n, w[300], sum[301], f[301][301], g[301][301], h[301][301];
class TheExperiment
{
public:
	int countPlacements(vector<string> intensity, int m, int l, int a, int b)
	{
		for(int i = 0; i < intensity.size(); i++)
		{
			for(int j = 0; j < intensity[i].length(); j++)
				w[n++] = intensity[i][j] - '0';
		}
		for(int i = 0; i < n; i++)
			sum[i + 1] = sum[i] + w[i];
		g[0][0] = h[0][0] = 1;
		for(int i = 1; i <= n; i++)
		{
			g[i][0] = h[i][0] = 1;
			for(int j = 1; j <= m; j++)
			{
				for(int k = i - l; k < i; k++)
				{
					if(sum[i] - sum[k] >= a && sum[i] - sum[k] <= b)
					{
						g[i][j] = (g[i][j] + g[k][j - 1]) % p;
						if(i - k == l) //至少选择了一个顶端区域 
							f[i][j] = (f[i][j] + g[k][j - 1]) % p;
						else
							f[i][j] = (f[i][j] + f[k][j - 1]) % p;
					}
				}
				h[i][j] = (f[i][j] + h[i - 1][j]) % p;
				g[i][j] = (g[i][j] + h[i - 1][j]) % p; //转移到下一组 
			}
		}
		return h[n][m];
	}
};