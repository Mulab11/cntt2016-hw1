#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 1000010
using namespace std;
struct TheDivisionGame
{
	int sg[N],now[N];
	int p[40010],cnt;
	bool he[40010];
	int tot[31];
	void pre()
	{
		int i,j;
		for(i=2;i<=31638;i++)
		{
			if(!he[i]) cnt++,p[cnt]=i;
			for(j=1;j<=cnt&&i*p[j]<=31638;j++)
			{
				he[i*p[j]]=true;
				if(i%p[j]==0) break;
			}
		}
	}
	long long countWinningIntervals(int L, int R)
	{
		pre();
		int i,j,x,y;
		for(i=L;i<=R;i++)
		now[i-L+1]=i;
		for(i=1;i<=cnt;i++)
		{
			x=((L-1)/p[i]+1)*p[i];
			while(x<=R)
			{
				while(now[x-L+1]%p[i]==0)
				sg[x-L+1]++,now[x-L+1]/=p[i];
				x+=p[i];
			}
		}
		for(i=L;i<=R;i++)
		sg[i-L+1]+=(now[i-L+1]!=1);
		int n=R-L+1,tmp=0;
		for(i=1;i<=n;i++)
		{
			tmp^=sg[i];
			tot[tmp]++;
		}
		tot[0]++;
		long long ans=0;
		for(i=0;i<=31;i++)
		ans+=(long long)tot[i]*(tot[i]-1)/2;
		return (long long)(n+1)*n/2-ans;
	}
};