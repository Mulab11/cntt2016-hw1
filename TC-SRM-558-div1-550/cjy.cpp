#include<bits/stdc++.h>
#define G(a,S,n)for(auto _:S)for(auto X:_)X==' '?n++:a[n]=a[n]*10+X-48;n++
#define vs vector<string>
using namespace std;
int n,m,a[300],b[300],c[300],x,y,z,u,v,i,j;
long long s;
class Ear//枚举，二分
{
	public:
		long long getCount(vs A,vs B,vs C)
		{
			G(a,A,n);G(b,B,m);m=0;G(c,C,m);sort(a,a+n);
			for(i=0;i<m;i++)for(j=0;j<m;j++)if(c[i]>c[j])z=(b[i]-b[j])*c[i]/(c[i]-c[j]),x=lower_bound(a,a+n,b[i]-max(z,0))-a,y=lower_bound(a,a+n,b[j])-a,u=a+n-upper_bound(a,a+n,b[i]-min(z,0)),v=a+n-upper_bound(a,a+n,b[j]),s+=(y+y-x-1)*x/2*(v+v-u-1)*u/2;
			return s;
		}
};
