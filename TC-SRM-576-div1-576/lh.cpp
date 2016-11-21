#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TheExperiment{
	private:
		static const int maxn=55*6,mod=1000000009;
		int sum[maxn],dp[maxn][maxn][2],fz[maxn][maxn],n;
	
	public:
		int countPlacements(vector <string> intensity, int M, int L, int A, int B){
			string tmp;
			for (int i=0;i<intensity.size();++i) tmp+=intensity[i];
			n=tmp.length();
			for (int i=1;i<=n;++i) sum[i]=sum[i-1]+tmp[i-1]-'0';
			dp[0][0][0]=1;
			fz[0][0]=1;
			for (int i=1;i<=n;++i){
				for (int k=1;k<=M;++k){
					for (int j=i-1;j>=0&&j>i-L;--j) if (sum[i]-sum[j]>=A){
						if (sum[i]-sum[j]>B) break;
						(dp[i][k][0]+=dp[j][k-1][0])%=mod;
					}
					
					if (i>=L&&sum[i]-sum[i-L]>=A&&sum[i]-sum[i-L]<=B) dp[i][k][1]=dp[i-L][k-1][0];
					
					for (int j=i-1;j>=0&&j>=i-L;--j) if (sum[i]-sum[j]>=A){
						if (sum[i]-sum[j]>B) break;
						(dp[i][k][1]+=dp[j][k-1][1])%=mod;
					}
					for (int j=i-1;j>0&&j>i-L;--j) if (sum[i]-sum[j]>=A){
						if (sum[i]-sum[j]>B) break;
						(dp[i][k][0]+=fz[j-1][k-1])%=mod;
					}
					if (i>L&&sum[i]-sum[i-L]>=A&&sum[i]-sum[i-L]<=B) (dp[i][k][1]+=fz[i-L-1][k-1])%=mod;
					fz[i][k]=(fz[i-1][k]+dp[i][k][1])%mod;
//					printf("dp[%d][%d][1]=%d  fz=%d\n",i,k,dp[i][k][1],fz[i][k]);
				}
				fz[i][0]=fz[i-1][0];
			}
			return fz[n][M]%mod;
		}
};
