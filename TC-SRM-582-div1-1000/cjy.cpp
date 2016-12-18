#include<bits/stdc++.h>
#define LL long long
#define N 500005
#define M 20002
using namespace std;
int u[N],p2[N],p3[N],i,j,k;
vector<int> d[M],s[M];
LL sqr2(LL x)
{
	LL m,l=1,r=x;
	while(l<r)if(m=l+r+1>>1,x/m/m)l=m;else r=m-1;
	return l;
}
LL sqr3(LL x)
{
	LL m,l=1,r=x;
	while(l<r)if(m=l+r+1>>1,x/m/m/m)l=m;else r=m-1;
	return l;
}
LL C(LL n)
{
	LL S=0,i,k,y,x,g,z;
	for(i=1;i*i*i<=n;i++)if(!p2[i])S+=sqr2(n/i)-i;
	for(i=1;i*i*i*i<=n;i++)if(!p3[i])for(k=sqr3(i);k;k--)if(g=__gcd(k*k,i),x=k*k/g,z=sqr3(n/i)/x,y=i/__gcd(k*k,i),!p2[y])
		for(auto j : d[y])S+=u[j]*(s[j][z/j]-s[j][i/x/j]);
	return S;
}
class SemiPerfectPower
{
	public:
		LL count(LL l,LL r)
		{
			for(i=1;i<M;i++)for(j=i;j<M;j+=i)d[j].push_back(i);
			for(i=2;i*i<N;i++)
			{
				for(j=i*i;j<N;j+=i*i)p2[j]=1;
				for(j=i*i*i;j<N;j+=i*i*i)p3[j]=1;
			}
			for(u[1]=1,i=2;i<M;i++)u[i]=(p2[i]?0:-u[i/d[i][1]]);
			for(i=1;i<M;i++)for(s[i].push_back(k=0),j=i;j<N;j+=i)s[i].push_back(k+=!p2[j]);
			return C(r)-C(l-1);
		}
};
