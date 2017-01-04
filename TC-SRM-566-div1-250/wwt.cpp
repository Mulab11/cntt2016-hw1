#include <bits/stdc++.h>

using namespace std;

class PenguinSledding
{
public:
	long long countDesigns(int numCheckpoints, vector <int> checkpoint1, vector <int> checkpoint2)
	{
		long long ans = 0;
		static int c[100];
		static bool lk[105][105];
		memset(c,0,sizeof c);
		//假如所有线段的交集只有一个点，那么他就是合法的。这种情况可以很容易的计出来。
		for(int i = 0;i < checkpoint2.size();i ++)
		{
			lk[checkpoint1[i]][checkpoint2[i]] = lk[checkpoint2[i]][checkpoint1[i]] = 1;
			c[checkpoint1[i]] ++,c[checkpoint2[i]] ++;
		}
		//一个三角形也是合法的
		for(int i = 1;i <= numCheckpoints;i ++)
			for(int j = 1;j < i;j ++)
				for(int k = 1;k < j;k ++)
					if (lk[k][j] && lk[k][i] && lk[i][j]) ++ ans;
		for(int i = 1;i <= numCheckpoints;i ++)
			ans += (1ll << c[i]) - 1;
		return ans - checkpoint2.size() + 1;

	}
};
