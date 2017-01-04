#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll f[55][105];

class MonstersValley
{
public:
	int minimumPrice(vector<long long> dread, vector <int> price)
	{
		memset(f,0,sizeof f);
		//设f[i][j]表示考虑前i头怪兽，用了j的代价，最大的随从和是多少。转移判一判买不买以及合不合法即可。
		int n = dread.size();
		for(int i = 0;i < n;i ++)
		{
			for(int j = 0;j <= 2 * n;j ++) f[i + 1][j] = -(1ll << 53);
			for(int j = 0;j <= 2 * n;j ++)
			{
				if (f[i][j] >= dread[i]) f[i + 1][j] = max(f[i + 1][j],f[i][j]);
				f[i + 1][j + price[i]] = max(f[i + 1][j + price[i]],f[i][j] + dread[i]);
			}
		}
		for(int j = 0;j <= 2 * n;j ++)
			if (f[n][j] >= 0) return j;
	}
};
