#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class AlternateColors2{
	private:
		static const int maxn=100050;
		long long dp[maxn][8][3];
		int trs[8][3];
	public:
		long long countWays(int n, int k){
			for (int i=1;i<8;++i){
				for (int j=0;j<3;++j){
					for (int t=1;t<=3;++t) if (i&(1<<((j+t)%3))){
						trs[i][j]=(j+t)%3;
						break;
					}
//					printf("trs[%d][%d]=%d\n",i,j,trs[i][j]);
				}
			}
			dp[1][7][0]=1;
			for (int i=1;i<k;++i)
			for (int sta=7;sta>0;--sta)
			for (int now=0;now<3;++now){
				int tt=trs[sta][now];
				dp[i+1][sta][tt]+=dp[i][sta][now];
				if (tt!=now){
					int nn=sta^(1<<tt);
					int ttt=trs[nn][tt];
					dp[i+1][nn][ttt]+=dp[i][sta][now];
					if (ttt!=tt){
						int nnn=nn^(1<<ttt);
						dp[i+1][nnn][trs[nnn][ttt]]+=dp[i][sta][now];
					}
				}
			}
			for (int i=1;i<8;++i){
				dp[k][i][1]=dp[k][i][2]=0;
			}
			for (int i=k;i<n;++i)
			for (int sta=7;sta>0;--sta)
			for (int now=0;now<3;++now){
				int tt=trs[sta][now];
				dp[i+1][sta][tt]+=dp[i][sta][now];
				if (tt!=now){
					int nn=sta^(1<<now);
					dp[i+1][nn][trs[nn][tt]]+=dp[i][sta][now];
					if (tt!=trs[nn][tt]){
						int ttt=trs[nn][tt];
						int nnn=nn^(1<<tt);
						dp[i+1][nnn][trs[nnn][ttt]]+=dp[i][sta][now];
					}
				}
			}
			long long ans=0;
			for (int i=1;i<8;++i)
			for (int j=0;j<3;++j) ans+=dp[n][i][j];
			return ans;
		}
};
