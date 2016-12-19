#include <bits/stdc++.h>
using namespace std;
class Stamp
{
	int pid(char w)
	{
		switch(w)
		{
			case 'R':	return 1;
			case 'G':	return 2;
			case 'B':	return 4;
		}
		return 0;
	}
	void cmin(int &a, int b) {a > b ? a = b : 0;}
public:
	int getMinimumCost(string s, int k1, int k2)
	{
		const int N = s.size();
		int ans = 2e9;
		for(int len = 1; len <= N; ++len)
		{
			int f[N + 1][3];
			memset(f, 63, sizeof f);
			memset(f[0], 0, sizeof f[0]);
			for(int i = len; i <= N; ++i)
			{
				int set = 0;
				for(int j = 1; j <= len; ++j) set |= pid(s[i - j]);
				for(int k = 0; k != 3; ++k) 
					if(__builtin_popcount(set | 1 << k) <= 1)
					{
						if(i - len >= 0) for(int t = 0; t != 3; ++t)
							cmin(f[i][k], f[i - len][t]);
						for(int j = 0; j != len; ++j) 
							cmin(f[i][k], f[i - j][k]);
						++f[i][k];
					}
			}
			int cur = 2e9;
			for(int k = 0; k != 3; ++k) cmin(cur, f[N][k]);
			if(cur <= N) cmin(ans, len * k1 + cur * k2);
		}
		return ans;
	}
}	user;