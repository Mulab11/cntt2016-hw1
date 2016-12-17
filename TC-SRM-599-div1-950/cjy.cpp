#include<bits/stdc++.h>
using namespace std;
int i,j,k,n,m,t=1,b[9999],c[9999][26],p[99],u[9],v[9],ac[65536],as[65536],at,P=1e9+7,f[99][65536],g[2][65536];
vector<int> e[9999],to[65536];
char w;
int B(int x,int p){if(b[x]){if(p)e[p].push_back(b[x]);p=b[x];}for(int i=25;~i;i--)if(c[x][i])B(c[x][i],p);}
int dp(int x)
{
	int j,E=1,O=0,y;
	for(auto i : e[x])dp(i);
	memset(g[E],0,sizeof(g[E]));g[E][0]=1;
	for(auto i : e[x])for(swap(O,E),memset(g[E],0,sizeof(g[E])),j=1;j<=at;j++)for(auto k : to[j])g[E][as[j]]=(1ll*g[O][k]*f[i][as[j]-k]+g[E][as[j]])%P;
	for(j=1;j<=at;j++)if(f[x][k=as[j]]=g[E][k],x<=n)for(y=k;y;y-=y&-y)f[x][k]=(f[x][k]+g[E][k-(y&-y)])%P;
}
class SimilarNames
{
	public:
		int count(vector<string> a,vector<int> a1,vector<int> a2)//虚树上按子集dp
		{
			for(n=a.size(),b[1]=n+1;i<n;b[k]=++i)for(k=1,j=0;j<a[i].size();k=c[k][w],j++)if(w=a[i][j]-'a',!c[k][w])c[k][w]=++t;
			for(B(1,0),m=a1.size(),i=t=0;i<m;i++)p[++t]=a1[i],p[++t]=a2[i];
			for(sort(p+1,p+t+1),t=unique(p+1,p+t+1)-p-1,i=1;i<=t;i++)b[p[i]]=i-1;
			for(i=0;i<m;i++)u[i]=b[a1[i]],v[i]=b[a2[i]];
			for(i=0;i<1<<t;i++)
			{
				for(j=0;j<m;j++)if((i>>u[j]&1)&&!(i>>v[j]&1))goto E;
				ac[as[++at]=i]=1;E:;
			}
			for(i=1;i<=at;i++)for(k=j=as[i];;j=k&(j-1))
			{
				if(ac[j]&&ac[k-j])to[i].push_back(j);
				if(!j)break;
			}
			for(dp(n+1),k=f[n+1][(1<<t)-1],i=n-t;i;i--)k=1ll*k*i%P;
			return k;
		}
};
