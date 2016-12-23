#include<bits/stdc++.h>
using namespace std;
class SkiResorts//分层最短路
{
	public:
		int n,v[2555],i,j,k;
		long long d[2555],s=1ll<<60;
		long long minCost(vector<string> e,vector<int> a)
		{
			for(n=e.size(),fill(d,d+n*n,1ll<<60);i<n;i++)d[i]=abs(a[i]-a[0]);
			for(i=0;i<n*n;i++)
			{
				for(k=-1,j=0;j<n*n;j++)if(!v[j]&&(k<0||d[j]<d[k]))k=j;
				for(v[k]=1,j=0;j<n*n;j++)if(e[k/n][j/n]=='Y'&&a[k%n]>=a[j%n])d[j]=min(d[j],d[k]+abs(a[j%n]-a[j/n]));
				if(k/n==n-1)s=min(s,d[k]);
			}
			return s==1ll<<60?-1:s;
		}
};
