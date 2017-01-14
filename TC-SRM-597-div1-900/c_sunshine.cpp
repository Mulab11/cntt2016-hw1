#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int M=1000000007,N=2000010;

class LittleElephantAndBoard
{
	public:
	int m,R,G,B;
	int T;
	int pw2[N+5];
	int fac[N+5],inv[N+5];
	
	int pow(int a,int b)//a^b
	{
		int s=1;
		for(;b;b>>=1,a=(LL)a*a%M)
			if(b&1)s=(LL)s*a%M;
		return s;
	}
	
	LL C(int x,int y)//combination(x,y)
	{return x<y||x<0||y<0?0:(LL)fac[x]*inv[y]%M*inv[x-y]%M;}
	
	int getNumber(int m,int R,int G,int B)
	{
		pw2[0]=1;fac[0]=1;
		for(int i=1;i<=N;i++)
		{
			pw2[i]=pw2[i-1]<<1;
			if(pw2[i]>=M)pw2[i]-=M;
			fac[i]=(LL)fac[i-1]*i%M;
		}
		inv[N]=pow(fac[N],M-2);
		for(int i=N-1;i>=0;i--)
			inv[i]=(LL)inv[i+1]*(i+1)%M;
		int i,j,k;
		LL ans=0;
		//Use the remaining color to represent the parttern of each column.
		//Calculate the new numbers of colors.
		//New limit is nothing but that the adjacent pairs do not have the same color.
		R=m-R;
		G=m-G;
		B=m-B;
		if(R>G)swap(R,G);
		if(R==0)
		{
			if(max(G-B,B-G)==1)return 2;
			else if(G==B)return 4;
			else return 0;
		}
		LL t;
		for(int k=1;k<=R;k++)
		{
			//k-1 segments of green
			t=(LL)C(G-1,k-2)*C(R-1,k-1)%M;
			ans+=(LL)t*C(k+k,B-(R-k+G-k+1));//Insert blue blocks
			//k segments of green
			//notice that GR..GR and RG..RG are both valid.
			t=(LL)C(G-1,k-1)*C(R-1,k-1)*2%M;
			ans+=(LL)t*C(k+k+1,B-(R-k+G-k));
			//k+1 segments of green
			t=(LL)C(G-1,k)*C(R-1,k-1)%M;
			ans+=(LL)t*C(k+k+2,B-(R-k+G-k-1));
			ans%=M;
		}
		ans=ans*2%M;
		if(ans<0)ans+=M;
		return ans;
	}
};

