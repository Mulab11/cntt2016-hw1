#include<bits/stdc++.h>
using namespace std;
class TheDevice
{
	public:
		inline int minimumAdditional(vector <string> plates)
		{
			int ans=0;
			for(int i=plates[0].size();i--;)
			{
				int cnt[2]={1,2};
				for(int j=plates.size();j--;)--cnt[plates[j][i]^'0'];
				ans=max(ans,max(cnt[0],0)+max(cnt[1],0));
			}
			return ans;
		}
};
