#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class RandomPaintingOnABoard{
	private:
		static const int maxn=21,maxm=1350;
		long long f[maxn+5][1370][2];
		int p[maxn][maxn];
		bool sig[1<<maxn];
		
//		double solve(int n){
//			sig[0]=true;
//			for (int i=0;i<n;++i){
//				dp[1<<i]=p[i];
//				sig[1<<i]=false;
//			}
//			double ret=0;
//			for (int i=1;i<(1<<n);++i){
//				int tmp=i&(-i);
//				if (tmp!=i){
//					dp[i]=dp[i^tmp]+dp[tmp];
//					sig[i]=!sig[i^tmp];
//				}
//				if (sig[i]) ret-=1/dp[i];
//				else ret+=1/dp[i];
//			}
//			printf("ret=%.10lf\n",ret);
//			return ret;
//		}
	
	public:
		double expectedSteps(vector<string> prob){
			int n=prob.size();
			int m=prob[0].length();
			int su=0;
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j) su+=(p[i][j]=prob[i][j]-'0');
			double ans=0;
			
			if (n<=m){
				for (int sta=0;sta<(1<<n);++sta){
					memset(f,0,sizeof(f));
					f[0][0][0]=1;
					int tmp=sta;
					int sig=0;
					while(tmp){
						tmp-=tmp&(-tmp);
						++sig;
					}
//					printf("sta=%d,sig=%d\n",sta,sig);
					for (int i=0;i<m;++i){
						int tp=0; 
						for (int j=0;j<n;++j) if (~sta&(1<<j)){
//							printf("xx %d\n",j);
							tp+=p[j][i];
						}
//						printf("tp=%d\n",tp);
						for (int j=su;j>=0;--j){
							f[i+1][j][0]=f[i][j][1];
							f[i+1][j][1]=f[i][j][0];
//							for (int k=0;k<2;++k)
//							printf("f[%d][%d][%d]=%lld\n",i+1,j,k,f[i+1][j][k]);
							if (j>=tp){
								f[i+1][j][0]+=f[i][j-tp][0];
								f[i+1][j][1]+=f[i][j-tp][1];
							}
//							for (int k=0;k<2;++k)
//							printf("f[%d][%d][%d]=%lld\n",i+1,j,k,f[i+1][j][k]);
						}
					}
					if (~sig&1){
						for (int i=0;i<su;++i){
							ans-=(double)su/(su-i)*f[m][i][0];
							ans+=(double)su/(su-i)*f[m][i][1];
						}
					}
					else{
						for (int i=0;i<su;++i){
							ans+=(double)su/(su-i)*f[m][i][0];
							ans-=(double)su/(su-i)*f[m][i][1];
						}
					}
				}
			}
			else{
				for (int sta=0;sta<(1<<m);++sta){
					memset(f,0,sizeof(f));
					f[0][0][0]=1;
					int tmp=sta;
					int sig=0;
					while(tmp){
						tmp-=tmp&(-tmp);
						++sig;
					}
//					printf("sta=%d,sig=%d\n",sta,sig);
					for (int i=0;i<n;++i){
						int tp=0; 
						for (int j=0;j<m;++j) if (~sta&(1<<j)){
//							printf("xx %d\n",j);
							tp+=p[i][j];
						}
//						printf("tp=%d\n",tp);
						for (int j=su;j>=0;--j){
							f[i+1][j][0]=f[i][j][1];
							f[i+1][j][1]=f[i][j][0];
//							for (int k=0;k<2;++k)
//							printf("f[%d][%d][%d]=%lld\n",i+1,j,k,f[i+1][j][k]);
							if (j>=tp){
								f[i+1][j][0]+=f[i][j-tp][0];
								f[i+1][j][1]+=f[i][j-tp][1];
							}
//							for (int k=0;k<2;++k)
//							printf("f[%d][%d][%d]=%lld\n",i+1,j,k,f[i+1][j][k]);
						}
					}
					if (~sig&1){
						for (int i=0;i<su;++i){
							ans-=(double)su/(su-i)*f[n][i][0];
							ans+=(double)su/(su-i)*f[n][i][1];
						}
					}
					else{
						for (int i=0;i<su;++i){
							ans+=(double)su/(su-i)*f[n][i][0];
							ans-=(double)su/(su-i)*f[n][i][1];
						}
					}
				}
			}
			return ans;
		}
};
