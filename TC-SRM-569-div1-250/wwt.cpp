#include <bits/stdc++.h>

using namespace std;

class TheDevice
{
public:
	int minimumAdditional(vector<string> plates)
	{
		static int rs[2][2]; //a opt b which opts will be the same
		rs[0][0] = 7;
		rs[0][1] = 6;
		rs[1][0] = 6;
		rs[1][1] = 3;
		int ans = 0;
		for(int bit = 0;bit < plates[0].length();bit ++)
		{
			int ls = 7;
			for(int i = 0;i < plates.size();i ++)
				for(int j = 0;j < plates.size();j ++)
					if (i != j) 
						ls &= rs[plates[i][bit] - 48][plates[j][bit] - 48];
			if (ls == 7) ans = 2; //we can not infer anything from the numbers themselves.
			if (__builtin_popcount(ls) > 1) ans = max(ans,1); //we need to add another plate to specify it.
		}
		return ans;
	}
};
