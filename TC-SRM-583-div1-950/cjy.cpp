#include<bits/stdc++.h>
using namespace std;
int a[15][25],S,s[25],i,j,k,t,v[4096],g[25],f[4096],r,n,m;
double res;
class RandomPaintingOnABoard
{
	public:
		double expectedSteps(vector<string> b)
		{
			for(n=b.size(),m=b[0].size();i<min(n,m);i++)for(j=0;j<max(n,m);j++)a[i][j]=(n<m?b[i][j]:b[j][i])-48,S+=a[i][j],s[j]+=a[i][j];
			if(n>m)swap(n,m);
			for(v[i=0]=-1;i<(1<<n);i++)
			{
				for(v[i]=i%2?-v[i/2]:v[i/2],j=0;j<m;j++)g[j]=s[j];
				for(j=t=0;j<n;j++)if(i>>j&1)for(k=0;k<m;k++)g[k]-=a[j][k],t+=a[j][k];
				for(memset(f,j=0,sizeof(f)),f[0]=r=1;j<m;j++)for(r+=g[j],k=r-1;k>=g[j];k--)f[k]-=f[k-g[j]];
				for(j=0;j<r;j++)if(t+j)res+=1.*v[i]*f[j]*S/(t+j);
			}
			return res;
		}
};
