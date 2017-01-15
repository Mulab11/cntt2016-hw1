#include <bits/stdc++.h>

using namespace std;

class TheTree
{
public:
	int maximumDiameter(vector<int> cnt)
	{
		int amax = 0,bmax = 0;//the biggest and the running-up depths
		vector<int> d;
		d.resize(cnt.size() + 1);
		d[0] = 1;
		for(int i = 0;i < cnt.size();i ++) d[i + 1] = cnt[i]; //the number of every depth
		int ans = 0;
		for(int i = cnt.size();i >= 0;i --)
		{
			for(int j = 0;j < d[i];j ++)
				if (i > amax) bmax = amax,amax = i; else //update amax,bmax
					if (i > bmax) bmax = i; 
			if (d[i] == 1) ans = max(ans,amax + bmax - 2 * i),bmax = 0; //we only have one point to be the lca,so the running up should be discarded
		}		
		return ans;
	}
};
