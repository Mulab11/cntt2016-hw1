#include<bits/stdc++.h>
using namespace std;
int f[1<<21],n,p[15],x[15],y[15],i,j,s,g,v[1<<21],c[15],d[15];
int DP(int s,int m,int X)
{
	int r=0,i=0;
	if(v[s])return f[s];v[s]=1;
	if(!X)
	{
		for(;i<n;i++)if(s/p[i]%3<2)c[x[i]]^=1,d[y[i]]^=1;
		for(i=0;i<15;i++)if(c[i]||d[i])r=99,c[i]=d[i]=0;
	}
	else if(!m){for(r=99;i<n;i++)if(s/p[i]%3<1&&!DP(s+2*p[i],m,X-1))r=0;}else for(;i<n;i++)if(s/p[i]%3<1)r=max(r,min(DP(s+p[i],m-1,X),DP(s+2*p[i],m-1,X-1)+1));
	return f[s]=r;
}
class MagicalHats
{
	public:
		int findMaximumReward(vector<string> S,vector<int> a,int m)
		{
			for(;i<S.size();i++)for(j=0;j<S[0].size();j++)if(S[i][j]=='H')x[n]=i,y[n++]=j;
			for(i=p[0]=1;i<14;i++)p[i]=p[i-1]*3;
			if(g=DP(0,m,a.size()),g>15)return -1;
			for(sort(a.begin(),a.end()),i=0;i<g;i++)s+=a[i];
			return s;
		}
};
