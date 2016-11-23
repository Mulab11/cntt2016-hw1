#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>
using namespace std;

class WolfInZooDivOne{
	static const int maxn=310,mod=1000000007;
	int dp[maxn][maxn];
	int sum[maxn][maxn];
	int pre[maxn];
	
	public:
		int count(int N, vector<string> L, vector<string> R){
			for (int i=0;i<N;++i) pre[i]=i;
			stringstream aa,bb;
			for (auto &i:L) aa<<i;
			for (auto &i:R) bb<<i;
			
			int l,r;
			while(aa>>l){
				bb>>r;
				for (int i=l;i<=r;++i) pre[i]=min(pre[i],l);
			}
			
			int ans=N+1;
			for (int i=1;i<N;++i){
				for (int j=0;j<i;++j){
					if (pre[i]==0) dp[i][j]=1;
					else dp[i][j]=(sum[j][pre[i]-1]+1)%mod;
//					printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
					ans=(ans+dp[i][j])%mod;
				}
				sum[i][0]=dp[i][0];
				for (int j=1;j<=N;++j) sum[i][j]=(sum[i][j-1]+dp[i][j])%mod;
			}
			return ans;
		}
};
