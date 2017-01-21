// BEGIN CUT HERE

// END CUT HERE
#line 5 "SkiResorts.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

void Min(ll &x,ll y){if (y<x) x=y;}

const int maxn=52;

class SkiResorts{
	int n;
	ll dp[maxn][maxn];
	bool flag[maxn][maxn];
	public:
	long long minCost(vector <string> road, vector <int> altitude){
		n=altitude.size();
		memset(dp,63,sizeof(dp));
		for (int i=0;i<n;++i) dp[0][i]=abs(altitude[i]-altitude[0]);
		memset(flag,0,sizeof(flag));
		for (;;){
			int i0=-1,j0=-1;
			for (int i=0;i<n;++i)for (int j=0;j<n;++j)
				if (!flag[i][j]&&(i0<0||dp[i][j]<dp[i0][j0]))
					i0=i,j0=j;
			if (i0<0||dp[i0][j0]>(1LL<<60)) break;
			flag[i0][j0]=1;
			if (i0==n-1) return dp[i0][j0];
			for (int j=0;j<n;++j)if (altitude[j]<=altitude[j0])
				for (int i=0;i<n;++i)if (road[i][i0]=='Y')
					Min(dp[i][j],dp[i0][j0]+abs(altitude[i]-altitude[j]));
		}
		return -1;
	}
};
