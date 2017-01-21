#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define eps 1e-8
using namespace std;

const int MAXN = 50;
int sum[MAXN][MAXN];
int d[MAXN];
queue <int> q;

class ColorfulWolves
{
	public:
		int getmin(vector <string> colormap)
		{
			int n = colormap.size();
			memset(d, -1, sizeof(d));
			for(int i = 0; i < n; i ++)
			{
				for(int j = 0; j < n; j ++)
				{
					if(colormap[i][j] =='Y')
					{
						sum[i][j] = 1;
					}
					else
					{
						sum[i][j] = 0;

					}
					if(j)
					{
						sum[i][j] += sum[i][j - 1];
					}
				}
			}
			while(! q.empty())
			{
				q.pop();
			}
			d[n - 1] = 0;
			q.push(n - 1);
			while(! q.empty())
			{
				int u = q.front();
				q.pop();
				if(! u)
				{
					continue;
				}
				for(int i = 0; i < n; i ++)
				{
					if(colormap[i][u] == 'Y')
					{
						if(d[i] == -1 || d[i] > d[u] + sum[i][u - 1])
						{
							d[i] = d[u] + sum[i][u - 1];
							q.push(i);
						}
					}
				}
			}
			return d[0];
		}
};
