#include <bits/stdc++.h>

using namespace std;

class TrafficCongestion
{
public:
	int theMinCars(int treeHeight)
	{
		static int f[1000005];
		memset(f,0,sizeof f);
		f[0] = f[1] = 1;
		int sum = 0,mo = int(1e9) + 7;
		for(int i = 2;i <= treeHeight;i ++) //f[i] = 1 + 2 * \sum_{j=0}^{i-2} f[j]
		{
			sum = (sum + f[i - 2]) % mo;
			f[i] = (2ll * sum + 1) % mo;
		}
		return f[treeHeight];
	}
};
