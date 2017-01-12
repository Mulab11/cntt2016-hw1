#include<bits/stdc++.h>
using namespace std;
const int MAXN=5005,oo=2147483647,dx[]={-1,0,1,0},dy[]={0,-1,0,1};
int i,j,k,l,N,s,t,g[MAXN],d[MAXN],ans,T,n,m;
char c[55][55];
struct edge
{
	int c,v;
	edge *n,*b;
}P[MAXN*10],*X,*f[MAXN],*tf[MAXN],*Null=new edge();
inline void add(int u,int v,int c)
{
	X->v=v;
	X->b=X+1;
	X->c=c;
	X->n=f[u];
	f[u]=X++;
	X->v=u;
	X->b=X-1;
	X->c=0;
	X->n=f[v];
	f[v]=X++;
}
int sap(int now,int flow)
{
	if(now==t)return flow;
	int sum=0,tmp;
	for(edge *i=tf[now];i!=Null;i=i->n)if(i->c&&d[i->v]+1==d[now])
	{
		tmp=sap(i->v,min(flow-sum,i->c));
		i->c-=tmp;
		i->b->c+=tmp;
		tf[now]=i;
		if((sum+=tmp)==flow)return sum;
		if(d[s]==N)return sum;
	}
	if(!(--g[d[now]]))d[s]=N-1;
	++g[++d[now]];
	tf[now]=f[now];
	return sum;
}
class BoardPainting
{
    public:
        int minimalSteps(vector <string> target)
        {
            n=target.size();
            m=target[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)c[i+1][j+1]=target[i][j];
            s=0;
            t=N=n*m+1;
            X=P;
            for(i=0;i<=t;i++)f[i]=Null;
            for(i=1;i<=n;i++)for(j=1;j<=m;j++)if(c[i][j]=='#')for(k=0;k<4;k++)if(c[i+dx[k]][j+dy[k]]=='#')add((i-1)*m+j,(i+dx[k]-1)*m+j+dy[k],1);//建图 
            else if(k&1)add(s,(i-1)*m+j,1);
            else add((i-1)*m+j,t,1);
            for(i=0;i<=t;i++)tf[i]=f[i];
            while(d[s]<N)ans+=sap(s,oo);//SAP求最小割 
            return ans>>1;//计算答案 
        }
};