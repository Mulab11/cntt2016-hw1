#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class MonstersValley{
	private:
		static const int maxn=55;
		long long dp[maxn][maxn<<1];
	public:
		int minimumPrice(vector<long long> dread, vector <int> price){
			memset(dp,-1,sizeof(dp));
			dp[0][0]=0;
			int n=dread.size(),m=n<<1;
			for (int i=1;i<=n;++i){
				long long w=dread[i-1];
				int c=price[i-1];
				for (int j=1;j<=m;++j){
					if(dp[i-1][j]>=w) dp[i][j]=dp[i-1][j];
					if (j>=c&&dp[i-1][j-c]!=-1) dp[i][j]=max(dp[i][j],dp[i-1][j-c]+w);
//					printf("dp[%d][%d]=%lld\n",i,j,dp[i][j]);
				}
			}
			for (int j=0;j<=m;++j) if (dp[n][j]!=-1) return j;
		}
};
