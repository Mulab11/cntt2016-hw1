// BEGIN CUT HERE

// END CUT HERE
#line 5 "MonstersValley.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class MonstersValley{
	int n;
	ll dp[maxn][maxn*2];
	public:
	int minimumPrice(vector<long long> dread, vector <int> price){
		n=dread.size();
		memset(dp,-1,sizeof(dp));
		dp[0][0]=0;
		for (int i=0;i<n;++i)for (int j=0;j<=2*i;++j)if (dp[i][j]>=0){
			dp[i+1][j+price[i]]=max(dp[i+1][j+price[i]],dp[i][j]+dread[i]);
			if (dp[i][j]>=dread[i]) dp[i+1][j]=max(dp[i+1][j],dp[i][j]);
		}
		int ret=-1;
		for (int j=0;j<=n*2;++j)
			if (dp[n][j]>=0){ret=j;break;}
		return ret;
	}
};
