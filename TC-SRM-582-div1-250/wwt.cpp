#include <bits/stdc++.h>

using namespace std;

class SpaceWarDiv1
{
public:
	vector<int> a,b;
	vector<long long> c;

	bool ok(long long v)
	{
		//hall theorm
		for(auto p : b)
		{
			long long xcount = 0,ycount = 0;
			for(int i = 0;i < b.size();i ++)
				if (b[i] >= p) xcount += c[i];
			for(int i = 0;i < a.size();i ++)
				if (a[i] >= p) ycount += v;
			if (ycount < xcount) return 0; 
		}
		return 1;
	}

	long long minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount)
	{
		a = magicalGirlStrength;
		b = enemyStrength;
		c = enemyCount;
		long long l = 0,r = (1ll << 57),tmp = -1;
		for(long long mid;l <= r;)
		{
			mid = l + r >> 1;
			if (ok(mid)) tmp = mid,r = mid - 1; else l = mid + 1;
		}
		return tmp;
	}
};
