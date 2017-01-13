#include<bits/stdc++.h>
using namespace std;
int p[50000],g[1<<20],x[1<<20],t[32],i,j,n;
long long s;
class TheDivisionGame
{
	public:
		long long countWinningIntervals(int l,int r)
		{
			for(n=r-l+1;i<n;i++)x[i]=l+i;
			for(i=2;i*i<=r;i++)if(!p[i])
			{
				for(j=i*i;j<50000;j+=i)p[j]=1;
				for(j=(i-l%i)%i;j<n;j+=i)while(x[j]%i==0)g[j]++,x[j]/=i;
			}
			for(i=0;i<n;i++)g[i]+=x[i]>1;
			for(t[i=j=0]=1;i<n;i++)s+=t[j^=g[i]]++;
			return 1ll*n*(n+1)/2-s;
		}
};
