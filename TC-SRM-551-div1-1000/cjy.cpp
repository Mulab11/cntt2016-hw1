#include<bits/stdc++.h>
using namespace std;
int P=1e9+7,n,m,g[55][55],f[55],c[55][55],i,j,u,v,t,b[55],x,e,S;
vector<int> L[55],R[55];
int V(int x){int r=1,n=P-2;for(;n;n/=2,x=1ll*x*x%P)if(n&1)r=1ll*r*x%P;return r;}
class SweetFruits
{
	public:
		int countTrees(vector<int> a,int M)
		{
			for(n=a.size();i<n;i++)if(a[i]!=-1)b[m++]=a[i];
			for(i=0;i<=n;i++)for(j=c[i][0]=1;j<=i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%P;
			for(t=m/2,i=0;i<1<<t;L[u].push_back(v),i++)for(j=u=v=0;j<t;j++)if(i>>j&1)u++,v+=b[j];
			for(i=0;i<1<<m-t;R[u].push_back(v),i++)for(j=u=v=0;j<m-t;j++)if(i>>j&1)u++,v+=b[j+t];
			for(x=0;x<=m;x++)
			{
				for(memset(g,0,sizeof(g)),u=1;u<=n;u++)for(v=u+1;v<=n;v++)if(v>m||u<=x&&v<=x)g[u][u]++,g[v][v]++,g[u][v]--,g[v][u]--;
				for(v=i=1;i<n;i++)
				{
					for(j=i;j<n;j++)if(g[j][i])break;
					if(j!=i)for(v=-v,u=i;u<n;u++)swap(g[i][u],g[j][u]);
					for(j=i+1;j<n;j++)for(e=1ll*g[j][i]*V(g[i][i])%P,u=i;u<n;u++)g[j][u]=(g[j][u]-1ll*e*g[i][u])%P;
				}
				for(i=1;i<n;i++)v=1ll*v*g[i][i]%P;f[x]=(v+P)%P;
				for(i=0;i<x;i++)f[x]=(f[x]+P-1ll*c[x][i]*f[i]%P)%P;
			}for(i=0;i<=m-t;i++)sort(R[i].begin(),R[i].end());
			for(u=0;u<=t;u++)for(sort(L[u].begin(),L[u].end()),v=0;v<=m-t;v++)for(i=L[u].size()-1,j=0;~i;S=(1ll*j*f[u+v]+S)%P,i--)for(;j<R[v].size()&&L[u][i]+R[v][j]<=M;j++); 
			return S;
		}
};
