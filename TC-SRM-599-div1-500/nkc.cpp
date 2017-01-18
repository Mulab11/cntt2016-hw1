#include<iostream>
#include<cstdio>
#include<cmath>
#define N 5010
#define M 1000000
using namespace std;
int n,s,to[M],l[M],ne[M],pre[N];
void add(int u,int v,int c)
{to[++s]=v;l[s]=c;ne[s]=pre[u];pre[u]=s;}
struct FindPolygons
{
	double minimumPolygon(int L)
	{
		if(L&1||L==2) return -1;
		for(int i=0;i<=L;i++)
		for(int j=0;j<=L;j++)
		{
			int x=sqrt(i*i+j*j);
			if(i*i+j*j==x*x) add(i,j,x);
		}
		int ans=1e9;
		for(int i=1;i<=L;i++)
		for(int j=pre[i];j;j=ne[j])
		{
			int o=L-l[j];
			for(int p=1;p<=o;p++)
			for(int r=pre[p];r;r=ne[r])
			if(o>=l[r])
			{
				int u=o-l[r];
				if(i*p!=to[r]*to[j])
				{
					int x=abs(i-to[r]),y=abs(p-to[j]),z=x*x+y*y,t=sqrt(z);
					if(t*t==z&&t==u) ans=min(ans,max(max(l[j],l[r]),t)-min(min(l[j],l[r]),t));
				}
				int x=i+to[r],y=abs(p-to[j]),z=x*x+y*y,t=sqrt(z);
				if(t*t==z&&t==u) ans=min(ans,max(max(l[j],l[r]),t)-min(min(l[j],l[r]),t));
			}
		}
		cout<<ans<<endl;
		if(ans<1e9) return ans;
		return (L/2)&1?1:0;
	}
};