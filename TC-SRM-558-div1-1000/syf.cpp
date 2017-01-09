//============================================================================
// Author       : Sun YaoFeng
//============================================================================

/*
构图，跑最小割
*/

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

const int MAX=40000;
const int INF=100000000;

int n,m,S,T;
int walk[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

int getnum(char a)
{
    if(a<='9' && a>='0')return a-'0';
    if(a<='z' && a>='a')return a-'a'+10;
    if(a<='Z' && a>='A')return a-'A'+36;
    return 0;
}

int U(int i,int j){return (i-1)*m+j;}
int V(int i,int j){return (i-1)*m+j+n*m;}

struct Edge
{
    int t,next,C,flow;
}e[MAX*4];
int Begin[MAX],h[MAX],gap[MAX],tot;

void addedge(int x,int y,int C)
{
    e[tot].t=y;
    e[tot].next=Begin[x];
    Begin[x]=tot;
    e[tot].C=C;e[tot].flow=0;
    tot++;
}

void add(int u,int v,int C)
{
    if(!C)return;
    addedge(u,v,C);
    addedge(v,u,0);
}

int sap(int u,int flow)	//最大流
{
    if(u==T)return flow;
    int i,v,remain=flow,temp;
    for(i=Begin[u];i!=-1;i=e[i].next)
    {
        v=e[i].t;
        if(h[v]+1==h[u] && e[i].C>e[i].flow)
        {
            temp=min(remain,e[i].C-e[i].flow);
            temp=sap(v,temp);
            e[i].flow+=temp;
            e[i^1].flow-=temp;
            remain-=temp;
            if(!remain)return flow;
        }
    }
    --gap[h[u]];
    if(!gap[h[u]])h[S]=T+1;
    ++h[u];
    ++gap[h[u]];
    return flow-remain;
}

struct SurroundingGame
{
    int maxScore(vector<string> a,vector<string> b)
    {
        int ans=0,nx,ny,i,j,k;
        n=a.size();m=a[0].size();
        S=2*n*m+1,T=2*n*m+2;
        memset(Begin,-1,sizeof Begin);
        for(i=1;i<=n;++i)
            for(j=1;j<=m;++j)
            {
                int c=getnum(a[i-1][j-1]),v=getnum(b[i-1][j-1]);
            //    ans+=good+max(good-cost,0);
			
				ans+= v << 1;
			
            //    int dif=good-cost;
              
			  if((i+j)%2==1)	//黑白染色
                {
					add(S, U(i, j), c);
					add(U(i, j), T, v);
					add(S, V(i, j), v);
					add(V(i, j), U(i, j), v);
					
                //    add(S,V(i,j),good);
                 //   add(V(i,j),U(i,j),INF);
                    for(k=0;k<4;++k)
                    {
                        nx=i+walk[k][0],ny=j+walk[k][1];
                        if(nx>=1 && nx<=n && ny>=1 && ny<=m)
                        {
                            add(V(i,j), U(nx,ny), INF);
                        }
                    }
                //    add(S,U(i,j),max(-dif,0));
                 //   add(U(i,j),T,max(0,dif));
                }
                else
                {
                    add(S, U(i, j), v);
					add(U(i, j), T, c);
					add(V(i, j), T, v);
					add(U(i, j), V(i, j), v);
					
					for(k=0;k<4;++k)
                    {
                        nx=i+walk[k][0],ny=j+walk[k][1];
                        if(nx>=1 && nx<=n && ny>=1 && ny<=m)
                        {
                            add(U(nx,ny), V(i,j), INF);
                        }
                    }
                }
            }
        memset(h,0,sizeof h);
        memset(gap,0,sizeof gap);
        gap[0]=T;
        while(h[S]<T+1)
            ans-=sap(S,INF);
        return ans;
    }
};