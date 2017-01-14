#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class TheDevice
{
	public:
	int cnt[55][2];
	int minimumAdditional(vector<string> plates)
	{
		//Each bit must be tested by 0~1 and 1~1, so at least two "1"s and one "0" is required. 
		int n=plates.size(),m=plates[0].size();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				cnt[j][plates[i][j]-'0']++;
		//cnt[j][c]: the number of c which occur at position j.
		int ans=0;
		for(int j=0;j<m;j++)
			ans=max(ans,max(1-cnt[j][0],0)+max(2-cnt[j][1],0));
		return ans;
	}
};

