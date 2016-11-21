#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class KingdomAndCities{
	private:
		static const int maxn=55,mod=1000000007,inv2=500000004;
		long long dp[maxn][maxn],C[maxn*maxn][maxn];
		void getC(){
			C[0][0]=1;
			for (int i=1;i<=1300;++i){
				C[i][0]=1;
				for (int j=1;j<=60&&j<=i;++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
			}
			return;
		}
		int cal(int a){return a*(a-1)/2;}
		long long cal1(int n,int K){
			if (n<3) return 0;
			if (K<2) return 0;
			/*
			 /##
			o ##
			 \##
			*/
			long long ret=dp[n-1][K-2]*C[n-1][2]%mod;
			
			/*
			 /##
			o
			 \##
			*/
			for (int i=1;i<n-1;++i)
			for (int j=i-1;j<=K-2;++j)
			(ret+=dp[i][j]*dp[n-1-i][K-2-j]%mod*C[n-1][i]%mod*i*(n-1-i)%mod*inv2)%=mod;
			return ret;
		}
		long long cal2(int n,int K){
			if (n<3) return 0;
			if (K<3) return 0;
			long long ret=0;
			/*
			  ##
			 /##\
			o ## o
			 \##/
			  ##
			*/
			if (K>=4) (ret+=dp[n-2][K-4]*C[n-2][2]%mod*C[n-2][2])%=mod;
			/*
			##   ##   ##
			##-o-##-o-##
			##   ##   ##
			*/
			if (K>=4){
				for (int i=1;i<n-2;++i)
				for (int k=i-1;k<=K-4;++k)
				for (int j=1;i+j<n-2;++j)
				for (int t=j-1;t+k<=K-4;++t){
					(ret+=dp[i][k]*dp[j][t]%mod*dp[n-2-i-j][K-4-k-t]%mod*C[n-2][i]%mod*C[n-2-i][j]%mod*i*(n-2-i-j)*j*j%mod)%=mod;
				}
			}
			
			/*
			##   ##\
			##-o-## o
			##   ##/
			*/
			if (K>=4){
				for (int i=1;i<n-2;++i)
				for (int k=i-1;k<=K-4;++k)
				(ret+=dp[i][k]*dp[n-2-i][K-4-k]%mod*C[n-2][i]%mod*i*(n-2-i)%mod*C[n-2-i][2]%mod*2ll)%=mod;
			}
			
			/*
			##     ##
			##-o-o-##
			##     ##
			*/
			for (int i=1;i<n-2;++i)
			for (int k=i-1;k<=K-3;++k)
			(ret+=dp[i][k]*dp[n-2-i][K-3-k]%mod*C[n-2][i]%mod*i*(n-2-i)%mod)%=mod;
			
			/*
			   o--o
			  /    \
			 ########
			
			*/
			(ret+=dp[n-2][K-3]*(n-2)*(n-2))%=mod;
			
			/*
			  ##
			 /##\
			o    o
			 \##/
			  ##
			*/
			
			for (int i=1;i<n-2;++i)
			for (int k=i-1;k<=K-4;++k)
			(ret+=dp[i][k]*dp[n-2-i][K-4-k]%mod*C[n-2][i]%mod*i*i*(n-2-i)*(n-2-i)%mod*inv2)%=mod;
			return ret;
		}
	public:
		int howMany(int n, int m, int K){
			if (K<n-1||K>cal(n)) return 0;
			getC();
			dp[1][0]=1;
			for (int i=2;i<=n;++i){
				int ct=cal(i);
				for (int j=i-1;j<=K;++j){
					dp[i][j]=C[ct][j];
					for (int k=1;k<i;++k)
					for (int e=k-1;e<=j;++e)
					dp[i][j]=(dp[i][j]-C[i-1][k-1]*dp[k][e]%mod*C[cal(i-k)][j-e]%mod+mod)%mod;
				}
			}
			if (m==0) return dp[n][K];
			else if (m==1)	return cal1(n,K);
			else if (m==2) return cal2(n,K);
		}
};
