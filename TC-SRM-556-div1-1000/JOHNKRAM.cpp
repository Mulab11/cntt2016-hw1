#include<bits/stdc++.h>
using namespace std;
const int MAXN=105,oo=2147483647;
int i,j,k,l,N,s,t,g[MAXN*100],d[MAXN],ans,T,n,m;
char c[55][55];
struct edge
{
	int c,v;
	edge *n,*b;
}P[MAXN*100],*X,*f[MAXN],*tf[MAXN],*Null=new edge();
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
int sap(int now,int flow)//SAP算法 
{
	if(now==t)return flow;
	int sum=0,tmp;
	for(edge *i=tf[now];i!=Null;i=i->n)if(i->c&&d[i->v]+1==d[now])//加了当前弧优化 
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
int ask(int s1,int s2,int t1,int t2,int x,int y)//计算{s1,s2}到{t1,t2}的最大流 
{
    X=P;//预处理 
    memset(d,0,sizeof(d));
    memset(g,0,sizeof(g));
    for(i=ans=0;i<N;i++)f[i]=Null;
    for(i=0;i<n;i++)for(j=0;j<n;j++)if(c[i][j]=='O')add(i,j,2);//建图 
    else if(c[i][j]=='N')add(i,j,oo);
    add(s,s1,x);
    add(s,s2,y);
    add(t1,t,x);
    add(t2,t,y);
    for(i=0;i<N;i++)tf[i]=f[i];//当前弧预处理 
    while(d[s]<N)ans+=sap(s,oo);//SAP求最大流 
    return ans;
}
class OldBridges
{
    public:
        string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn)
        {
            n=bridges.size();
            s=n;
            t=n+1;
            N=n+2;
            for(i=0;i<n;i++)for(j=0;j<n;j++)c[i][j]=bridges[i][j];
            if(ask(a1,b1,a2,b2,an<<1,bn<<1)==(an+bn<<1)&&ask(a1,b2,a2,b1,an<<1,bn<<1)==(an+bn<<1))return "Yes";//判断是否有合法解 
            return "No";
        }
};