#include<bits/stdc++.h>
using namespace std;
int P=1e9+7,c[123456],i,j,s,p,m;
int Pow(int x,int y){int r=1;for(;y;x=1ll*x*x%P,y/=2)if(y&1)r=1ll*r*x%P;return r;}
int Calc(vector<int> a)
{
	for(i=a[s=0]-m;i<=a[0]+m;s=(s+p)%P,i+=2)
	{
		p=1;
		for(auto j : a)p=(abs(j-i)>m||abs(j-i-m)%2)?0:1ll*p*c[(m-abs(j-i))/2]%P;
	}
	return s;
}
class WolfPack
{
	public:
		int calc(vector<int> x,vector<int> y,int M)
		{
			for(i=c[0]=1,m=M;i<=m;i++)c[i]=1ll*c[i-1]*(m-i+1)%P*Pow(i,P-2)%P;
			for(i=0;i<x.size();i++)x[i]+=y[i],y[i]=x[i]-2*y[i];
			return 1ll*Calc(x)*Calc(y)%P;
		}
};
