#include<bits/stdc++.h>
using namespace std;
#define oo 1000000000
int n,m,a[10],b[10],i,l,r,s,t,A[10],B[10],ans,h[20],ne[2000],p[2000],w[2000],d[20],q[20],he,ta,P[10],tot;
bool g[10][10];
void add(int x,int y,int z)
{
    p[++m]=y;
    ne[m]=h[x];
    w[m]=z;
    h[x]=m;
    p[++m]=x;
    ne[m]=h[y];
    w[m]=0;
    h[y]=m;
}
bool bfs()
{
    memset(d,-1,sizeof(d));
    he=ta=0;
    d[q[ta++]=s]=0;
    while(he!=ta)for(int i=q[he++],j=h[i];j;j=ne[j])if(!~d[p[j]]&&w[j])d[q[ta++]=p[j]]=d[i]+1;
    return d[t]!=-1;
}
int dfs(int x,int f)
{
    if(x==t)return f;
    int i=h[x],j,k=f;
    for(;i;i=ne[i])if(d[p[i]]==d[x]+1)
    {
        j=dfs(p[i],min(f,w[i]));
        w[i]-=j;
        w[i^1]+=j;
        f-=j;
    }
    return k-f;
}
bool check()//判断取走块的顺序是否合法 
{
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(g[i][j]&&P[i]>P[j])return 0;
    return 1;
}
void Dfs(int x,int y)//搜索每种块是否在另外每种块的上面 
{
    if(x==n)
    {
        int i,j;
        for(i=0;i<n;i++)if(a[i]<0||b[i]<0)return;
        m=1;
        memset(h,0,sizeof(h));
        for(i=0;i<n;i++)//建图 
        {
            add(s,i,a[i]);
            add(i+n,t,b[i]);
        }
        add(2*n,t,oo);
        for(i=0;i<n;i++)for(j=0;j<n;j++)if(g[i][j])add(i,j+n,oo);
        for(i=j=0;i<n;i++)if(A[i]==1)add(i,2*n,oo);
        for(i=0;i<n;i++)j+=a[i];
        while(bfs())j-=dfs(s,oo);//Dinic跑最大流 
        if(j)return;
        for(i=0;i<n;i++)P[i]=i;
        tot=0;
        do tot+=check();while(next_permutation(P,P+n));//枚举取走块的顺序 
        if(tot>=l&&tot<=r)ans++;//判断方案数是否在合法区间内 
        return;
    }
    if(y==n)
    {
        Dfs(x+1,0);
        return;
    }
    Dfs(x,y+1);
    if(A[x]==A[y]+1)
    {
        a[x]--;
        b[y]--;
        g[x][y]=1;
        Dfs(x,y+1);
        g[x][y]=0;
        a[x]++;
        b[y]++;
    }
}
void dfs(int x)//搜索每一种块的高度 
{
    int i;
    if(x==n)
    {
        for(i=2;i<=n;i++)if(B[i]&&!B[i-1])return;//判断是否有某一层没有块 
        Dfs(0,0);
        return;
    }
    for(i=1;i<=n;i++)
    {
        B[A[x]=i]++;
        dfs(x+1);
        B[i]--;
    }
}
class CosmicBlocks
{
    public:
        int getNumOrders(vector <int> blockTypes, int minWays, int maxWays)
        {
            n=blockTypes.size();
            s=2*n+1;
            t=2*n+2;
            for(i=0;i<n;i++)a[i]=b[i]=blockTypes[i];
            l=minWays;
            r=maxWays;
            dfs(0);
            return ans;
        }
};