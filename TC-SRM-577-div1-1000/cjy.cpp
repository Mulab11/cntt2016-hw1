#include<bits/stdc++.h>
#define N 20010
using namespace std;
int T,h[N],l[N],e[N],c[N],v[N],f[N],t=1,O=1<<30,n,m,i,j,k,d[55][55],dx[4]={0,1,0,-1},dy[4]={1,0,-1,0},s;
void A(int x,int y){e[++t]=y,l[t]=h[x],h[x]=t,c[t]=1;e[++t]=x,l[t]=h[y],h[y]=t;}
int S(int x,int F)
{
	if(x==T)return F;
	int r=0,t,i;
	for(i=h[x];i;i=l[i])if(c[i]&&f[x]==f[e[i]]+1)if(t=S(e[i],min(F-r,c[i])),c[i]-=t,c[i^1]+=t,(r+=t)>=F||f[0]>T)return r;
	if(!--v[f[x]])f[0]=T+1;++v[++f[x]];
	return r;
}
class BoardPainting
{
	public:
		int minimalSteps(vector<string> a)
		{
			for(n=a.size(),m=a[0].size();i<n;i++)for(j=0;j<m;j++)if(a[i][j]=='#')d[i+1][j+1]=++T;
			for(++T,i=1;i<=n;i++)for(j=1;j<=m;j++)if(d[i][j])for(k=0;k<4;k++)if(d[i+dx[k]][j+dy[k]])A(d[i][j],d[i+dx[k]][j+dy[k]]);else k%2?A(d[i][j],T):A(0,d[i][j]);
			while(f[0]<=T)s+=S(0,O);
			return s/2;
		}
};
