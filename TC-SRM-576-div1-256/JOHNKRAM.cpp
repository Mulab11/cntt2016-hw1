#include<bits/stdc++.h>
using namespace std;
struct edge
{
    int s,t,d;
    bool operator<(const edge& y)const
    {
        return d<y.d;
    }
}e[10005];
int n,m,N,x,i,j,k,f[2505];
int get(int x)//并查集 
{
    if(f[x]==x)return x;
    return f[x]=get(f[x]);
}
class ArcadeManao
{
    public:
        int shortestLadder(vector <string> level, int coinRow, int coinColumn)
        {
            n=level.size();
            m=level[0].size();
            x=coinRow*m+coinColumn-m-1;
            for(i=0;i<=n*m;i++)f[i]=i;
            for(i=0;i<n;i++)for(j=0;j+1<m;j++)if(level[i][j]=='X'&&level[i][j+1]=='X')//横向边 
            {
                e[++N].s=i*m+j;
                e[N].t=i*m+j+1;
                e[N].d=0;
            }
            for(i=0;i<m;i++)for(j=0,k=-1;j<n;j++)if(level[j][i]=='X')//纵向边 
            {
                if(~k)
                {
                    e[++N].s=j*m+i;
                    e[N].t=k*m+i;
                    e[N].d=j-k;
                }
                k=j;
            }
            for(i=0;i<m;i++)//虚点到底部点 
            {
                e[++N].s=n*m-m+i;
                e[N].t=n*m;
                e[N].d=0;
            }
            sort(e+1,e+N+1);
            for(i=1;i<=N;i++)if(get(e[i].s)!=get(e[i].t))//最小生成树 
            {
                f[get(e[i].s)]=get(e[i].t);
                if(get(n*m)==get(x))return e[i].d;//已连通 
            }
        }
};