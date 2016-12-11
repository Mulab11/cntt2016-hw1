#include<bits/stdc++.h>
#define N 999999
using namespace std;
int T,h[N],l[N],e[N],c[N],v[N],f[N],t=1,O=1<<30,n,s,i,j,k;
void A(int x,int y,int z){e[++t]=y,l[t]=h[x],h[x]=t,c[t]=z;e[++t]=x,l[t]=h[y],h[y]=t,c[t]=0;}
int S(int x,int F){if(x==T)return F;int r=0,t,i;for(i=h[x];i;i=l[i])if(c[i]&&f[x]==f[e[i]]+1)if(t=S(e[i],min(F-r,c[i])),c[i]-=t,c[i^1]+=t,(r+=t)>=F||f[0]>T)return r;if(!--v[f[x]])f[0]=T+1;++v[++f[x]];return r;}
class FoxAndCity
{
	public:
		int minimalCost(vector<string>a,vector<int>b)//分层网络流		
		{
			n=a.size();T=n*n+n+1;
			for(A(0,1,0),A(n+1,T,O),j=1;j<=n;j++)A(j,j+1,O);
			for(i=2;i<=n;i++)for(k=b[i-1],A(0,i*n+i-n,O),A(i*n+i,T,O),j=1;j<=n;j++)A(i*n+i-n-1+j,i*n+i-n+j,(k-j)*(k-j));
			for(i=1;i<n;i++)for(j=i+1;j<=n;j++)if(a[i-1][j-1]=='Y')for(k=1;k<=n;k++)A(i*n+i-n+k,j*n+j-n+k-1,O),A(j*n+j-n+k,i*n+i-n+k-1,O);
			while(f[0]<=T)s+=S(0,O);
			return s;
		}
};
