// FST:计算组合数忘记判m>n返回0 
#include <cstdio>
#define MOD 1000000007
class LittleElephantAndBoard{
public:
	long long fac[1000010],ifac[1000010],pow2[1000010];
	long long inv(int a,int p){return a==1?1:(1+p*(a-inv(p%a,a)))/a%p;}
	long long C(int n,int m){return n<0||m<0||m>n?0:fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;}
	int solve(int n,int a,int b,int c){
		if(n==1)return 2; 
		int ans=0;
		for(int m=a-1;m<=a+1;m++){
			for(int s=0;s<=m;s++)if((n-a+s)%2==0&&(s+c-b)%2==0){
				ans=(ans+(m==a?2:1)*C(m,s)*C((n-a+s)/2-1,m-1)%MOD*C(s,(s+c-b)/2)%MOD*pow2[m-s])%MOD;
			}
		}
		return ans*2%MOD;
	}
	int getNumber(int M, int R, int G, int B){
		if(R>M||G>M||B>M)return 0;
		for(int i=fac[0]=pow2[0]=1;i<=M;i++)fac[i]=fac[i-1]*i%MOD,pow2[i]=(pow2[i-1]<<1)%MOD;
		ifac[M]=inv(fac[M],MOD);
		for(int i=M-1;i>=0;i--)ifac[i]=ifac[i+1]*(i+1)%MOD;
		return solve(M,M-R,M-G,M-B);
	}
};
