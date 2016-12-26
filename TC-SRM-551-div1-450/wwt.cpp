/*
直接令c[i][j]=i中比j小的'Y'个数，跑一个从0到n-1的最短路即可。
*/
#include <bits/stdc++.h>

using namespace std;

class ColorfulWolves
{
public:
	int getmin(vector<string> colormap)
	{
		int n = colormap.size();
		static int d[55];
		static bool out[55];
		memset(out,0,sizeof out);
		memset(d,60,sizeof d);
		d[0] = 0;
		for(;;) //dijkstra
		{
			int s = -1;
			for(int j = 0;j < n;j ++)
				if (!out[j] && (s == -1 || d[j] < d[s])) s = j;
			if (s == -1) break;
			out[s] = 1;
			for(int j = 0,c = 0;j < n;j ++)
				if (colormap[s][j] == 'Y')
				{
					if (d[s] + c < d[j])
						d[j] = d[s] + c;
					++ c;
				}
		}
		if (d[n - 1] > 1000000) d[n - 1] = -1;
		return d[n - 1];
	}
};
