#include<bits/stdc++.h>
#define N 999999
using namespace std;
int T,h[N],l[N],e[N],c[N],v[N],f[N],t=1,O=1<<30,n,s,i,j,d[55][55];
void A(int x,int y){e[++t]=y,l[t]=h[x],h[x]=t,c[t]=1;e[++t]=x,l[t]=h[y],h[y]=t,c[t]=0;}
int S(int x,int F){if(x==T)return F;int r=0,t,i;for(i=h[x];i;i=l[i])if(c[i]&&f[x]==f[e[i]]+1)if(t=S(e[i],min(F-r,c[i])),c[i]-=t,c[i^1]+=t,(r+=t)>=F||f[0]>T)return r;if(!--v[f[x]])f[0]=T+1;++v[++f[x]];return r;}
class FoxAndGo3
{
	public:
		int maxEmptyCells(vector<string>a)
		{
			n=a.size();T=n*n+1;
			for(i=0;i<n;i++)for(j=0;j<n;j++)if(a[i][j]=='.'||a[i][j]=='o')d[i][j]=++s;
			for(i=0;i<n;i++)for(j=0;j<n;j++)if(a[i][j]=='o')A(d[i][j],T);else if(a[i][j]=='.')//最小割			
			{
				A(0,d[i][j]);
				if(i&&a[i-1][j]=='o')A(d[i][j],d[i-1][j]);
				if(i<n-1&&a[i+1][j]=='o')A(d[i][j],d[i+1][j]);
				if(j&&a[i][j-1]=='o')A(d[i][j],d[i][j-1]);
				if(j<n-1&&a[i][j+1]=='o')A(d[i][j],d[i][j+1]);
			}
			while(f[0]<=T)s-=S(0,O);
			return s;
		}
};
