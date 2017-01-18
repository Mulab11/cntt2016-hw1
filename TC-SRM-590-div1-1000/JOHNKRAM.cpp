#include<bits/stdc++.h>
using namespace std;
const int MAXN=5005,oo=2147483647,dx[]={-1,0,1,0},dy[]={0,-1,0,1};
int i,j,k,l,N,s,t,g[MAXN],d[MAXN],ans,T,n,m;
char c[55][55];
struct edge
{
	int c,v;
	edge *n,*b;
}P[MAXN*40],*X,*f[MAXN],*tf[MAXN],*Null=new edge();
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
class FoxAndCity
{
    public:
        int minimalCost(vector <string> linked, vector <int> want)
        {
            n=linked.size();
            X=P;
            s=n*n;
            t=N=s+1;
            for(i=0;i<=t;i++)f[i]=Null;
            for(i=1;i<n;i++)
            {
                add(s,i*n,oo);
                add(i*n+n-1,t,oo);
                for(j=1;j<n;j++)add(i*n+j-1,i*n+j,(want[i]-j)*(want[i]-j));
            }
            for(add(n-1,t,oo),j=1;j<n;j++)add(j-1,j,oo);
            for(i=0;i<n;i++)for(j=0;j<n;j++)if(linked[i][j]=='Y')for(k=1;k<n;k++)add(i*n+k,j*n+k-1,oo);
            for(i=0;i<=t;i++)tf[i]=f[i];
            while(d[s]<N)ans+=sap(s,oo);
            return ans;
        }
};
