#include<bits/stdc++.h>
#define VI vector<int>
#define LL long long 
using namespace std;LL n,i,j,P=1e9+9,t,p,d;LL E(VI a,VI b,VI c,LL A,LL B,LL C=0)
{
	if(A<=0||B<=0||C<0)return 0;map<LL,vector<int> >F[4];
	for(i=0;i<n;F[t][p/2].push_back(d-p/2),i++)
	{
		if(t=0,b[i]-B==c[i]-C)t=2,p=A+a[i]-b[i]+B,d=a[i],j=A;
		if(c[i]-C==a[i]-A)t=3,p=B+b[i]-c[i]+C,d=b[i],j=B;
		if(a[i]-A==b[i]-B)t=1,p=C+c[i]-a[i]+A,d=c[i],j=C;
		if(!t||p>j*2||p<0||p%2)return 0;
	}
	for(p=t=1;t<4;t++)for(auto x:F[t])
	{VI e=x.second;
		if(sort(e.begin(),e.end()),x.first&&(e[0]||e.size()>1&&!e[1]))return 0;
		for(i=d=1;i<e.size();p=p*(d-!e[0])%P,i++)if(e[i]^e[i-1])d=i+1;
	}
	return p;
}LL G(VI a,VI b,VI c)
{
	for(i=j=0;i<n;i++)if(c[i]<c[j])j=i;LL A=a[j],B=b[j],C=c[j];
	return E(a,b,c,A-C,B-C)+E(a,b,c,C-A,B-C)+E(a,b,c,A-C,C-B)+E(a,b,c,A+C,B-C)+E(a,b,c,A-C,B+C);
}
class UnknownTree
{
	public:
		int getCount(VI a,VI b,VI c)
		{
			for(n=a.size();i<n;i++)if((LL)(a[i]+b[i]+c[i])<(LL)(a[j]+b[j]+c[j]))j=i;
			return(E(a,b,c,a[j],b[j],c[j])+G(a,b,c)+G(b,c,a)+G(c,a,b))%P;
		}
};
