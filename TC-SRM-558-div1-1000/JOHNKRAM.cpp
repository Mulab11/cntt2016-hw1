#include<bits/stdc++.h>
using namespace std;
const int MAXN=805,oo=2147483647,dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};
int i,j,k,l,N,s,t,g[MAXN*100],d[MAXN],ans,T,n,m,a[55][55],b[55][55];
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
int get(char c)//字符转数字 
{
    if(c<='9')return c-'0';
    if(c<='Z')return c-'A'+36;
    return c-'a'+10;
}
class SurroundingGame
{
    public:
        int maxScore(vector <string> cost, vector <string> benefit)
        {
            X=P;
            Null->n=Null->b=Null;
            n=cost.size();
            m=cost[0].size();
            s=2*n*m;
            t=2*n*m+1;
            N=t+1;
            for(i=0;i<N;i++)f[i]=Null;
            for(i=0;i<n;i++)for(j=0;j<m;ans+=get(benefit[i][j++]))if((i^j)&1)//黑点 
            {
                add(s,i*m+j,get(cost[i][j]));
                add(i*m+j,(i+n)*m+j,get(benefit[i][j]));
                for(k=0;k<4;k++)if(i+dx[k]>=0&&j+dy[k]>=0&&i+dx[k]<n&&j+dy[k]<m)//与相邻点连边 
                {
                    add(i*m+j,(i+dx[k]+n)*m+j+dy[k],oo);
                    add((i+n)*m+j,(i+dx[k])*m+j+dy[k],oo);
                }
            }
            else//白点 
            {
                add((i+n)*m+j,i*m+j,get(benefit[i][j]));
                add(i*m+j,t,get(cost[i][j]));
            }
            for(i=0;i<N;i++)tf[i]=f[i];//当前弧预处理 
            while(d[s]<N)ans-=sap(s,oo);//SAP求最小割 
            return ans;
        }
};