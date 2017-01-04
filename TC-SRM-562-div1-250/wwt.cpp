/*
对于每个点(m,n)，可以知道，假如他能覆盖到(x,y)，那么有x-m=y-n <= T,x-m>=0，从而推断出m<=x<=m+T,y=x+n-m。那么考虑重复计算的情况，
假如一个点(x,y)，既能被(m,n)覆盖，又能被(u,v),u<m覆盖，那么是不能被计入(m,n)中的。
但可以发现，此时必有m-n=u-v，那么我们只需要考虑(m,n)有效的x的范围即可，把重复的删掉即可。
*/
#include <bits/stdc++.h>

using namespace std;

class PastingPaintingDivOne
{
public:
	int r[55][55][2];

	vector<long long> countColors(vector <string> clipboard, int T)
	{
		T --;
		vector<long long> out;
		out.resize(3,0);
		int n = clipboard.size(),m = clipboard[0].length();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
			{
				if (clipboard[i][j] == '.') continue;
				r[i][j][0] = max(i,0),r[i][j][1] = i + T;
				//去重，求出还被之前的点覆盖的范围
				for(int u = 0;u < i;u ++)
					for(int v = 0;v < m;v ++)
						if (i - j == u - v && clipboard[u][v] != '.')
							r[i][j][0] = max(r[i][j][0],r[u][v][1] + 1);
				int bel;
				char c = clipboard[i][j];
				if (c == 'R') bel = 0;
				if (c == 'G') bel = 1;
				if (c == 'B') bel = 2;
				out[bel] += r[i][j][1] - r[i][j][0] + 1;
			}
		return out;
	}
};
