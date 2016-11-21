#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class RockPaperScissors{
	private:
		static const int maxn=53;
		long double pr[maxn][3];
		int n;
		long double sum[maxn][maxn][maxn],dp[maxn][maxn][maxn],C[maxn][maxn];
	
	public:
		double bestScore(vector<int> rockProb,vector<int> paperProb,vector<int> scissorsProb){
			n=rockProb.size();
			C[0][0]=1;
			for (int i=1;i<=n;++i){
				C[i][0]=1;
				for (int j=1;j<=i;++j) C[i][j]=C[i-1][j-1]+C[i-1][j];
			}
			for (int i=0;i<n;++i){
				pr[i][0]=rockProb[i]/300.0;
				pr[i][1]=paperProb[i]/300.0;
				pr[i][2]=scissorsProb[i]/300.0;
			}
			sum[0][0][0]=1;
			for (int i=0;i<n;++i){
				for (int x=i+1;x>=0;--x)
				for (int y=i+1-x;y>=0;--y)
				for (int z=i+1-x-y;z>=0;--z){
					if (x) sum[x][y][z]+=sum[x-1][y][z]*pr[i][0];
					if (y) sum[x][y][z]+=sum[x][y-1][z]*pr[i][1];
					if (z) sum[x][y][z]+=sum[x][y][z-1]*pr[i][2];
				}
			}
			for (int su=0;su<=n;++su)
			for (int x=su;x>=0;--x)
			for (int y=su-x;y>=0;--y){
				sum[x][y][su-x-y]/=C[n][su];
//				printf("sum[%d][%d][%d]=%Lf\n",x,y,su-y-x,sum[x][y][su-x-y]);
			}
			
			for (int x=n;x>=0;--x)
			for (int y=n-x;y>=0;--y)
			for (int z=n-x-y;z>=0;--z){
				if (sum[x][y][z]==0) dp[x][y][z]=0;
				else{
					long double p0=(x+1)*sum[x+1][y][z]/sum[x][y][z]/(x+y+z+1);
					long double p1=(y+1)*sum[x][y+1][z]/sum[x][y][z]/(x+y+z+1);
					long double p2=(z+1)*sum[x][y][z+1]/sum[x][y][z]/(x+y+z+1);
//					printf("now is (%d,%d,%d) p0=%Lf, p1=%Lf, p2=%Lf\n",x,y,z,p0,p1,p2);
					long double tmp=max(max(3*p2+p0,3*p1+p2),3*p0+p1);
					dp[x][y][z]=tmp+p0*dp[x+1][y][z]+p1*dp[x][y+1][z]+p2*dp[x][y][z+1];
				}
			}
			return dp[0][0][0];
		}
};
