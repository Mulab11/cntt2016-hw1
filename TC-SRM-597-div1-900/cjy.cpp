#include<iostream>
#include<cstdio>
using namespace std;
int x1,x2,x3,T,m,R,G,B,P=1000000007,ans,i,j[2100001],rv[2100001];
int pow(int x,int y)
{
	int r=1;
	while(y)
	{
		if(y&1) r=1ll*r*x%P;
		x=1ll*x*x%P;
		y>>=1;
	}
	return r;
}
int C(int x,int y){if(x<y||y<0)return 0;return 1ll*j[x]*rv[y]%P*rv[x-y]%P;}
struct LittleElephantAndBoard 
{
	public:
	    int getNumber(int m, int R, int G, int B)
		{
			for(j[0]=rv[0]=i=1;i<=2100000;i++)j[i]=1ll*j[i-1]*i%P,rv[i]=pow(j[i],P-2);
			x1=m-R; x2=m-G; x3=m-B;
			if(x1>x2)swap(x1,x2);
			if(x1==0)swap(x1,x3);
			for(i=1;i<=x1;i++)//分情况累计			
			{
				if(i>1)ans=(1ll*C(x1-1,i-1)*C(x2-1,i-2)%P*C(2*i,x3-1-(x1-i)-(x2-i))%P+ans)%P;
				if(i<x2)ans=(1ll*C(x1-1,i-1)*C(x2-1,i)%P*C(2*i+2,x3+1-(x1-i)-(x2-i))%P+ans)%P;
				ans=(2ll*C(x1-1,i-1)*C(x2-1,i-1)%P*C(2*i+1,x3-(x1-i)-(x2-i))%P+ans)%P;
			}
			return 2*ans%P;
		}
};
