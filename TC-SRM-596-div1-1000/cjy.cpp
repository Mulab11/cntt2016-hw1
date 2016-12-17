#include<bits/stdc++.h>
#define N 1000010
#define LL long long
using namespace std;
long long a[2][N],b[N],c[N],o,e=1,i=2,t=1,u,w,v,j,x,s,r,O=1e18,S;
class SparseFactorial
{
	public:
		LL getCount(LL L,LL R,LL m)
		{
			for(L--,x=m;m>1;i++)if(m%i==0)
			{
				for(swap(o,e),s=1,fill(b,b+N,O),fill(c,c+N,r=0);m%i==0;m/=i)s*=i,r++;
				for(u=0;u<i*r;u++)for(w=u*u,j=w%i;j<s;j+=i)if(b[j]==O)
				{
					for(v=(j+s-w%s)%s;v&&v%i==0;v/=i)c[j]++;
					if(c[j]>=r||!v)b[j]=w+1;
				}
				for(j=0;j<t*s;j++)a[e][j]=max(a[o][j%t],b[j%s]);t*=s;
			}
			for(i=0;i<x;i++)
			{
				if(w=(a[e][i]/x+(a[e][i]%x>i))*x+i,R>=w)S+=(R-w)/x+1;
				if(L>=w)S-=(L-w)/x+1;
			}
			return S;
		}
};
