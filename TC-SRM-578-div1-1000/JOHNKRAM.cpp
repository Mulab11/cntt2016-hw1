#include<bits/stdc++.h>
using namespace std;
int n,m,ans,A,i,h[105],ne[105],p[105],a[105][105],a1[105][105],lx[105],ly[105],t[105];
bool bx[105],by[105];
bool find(int x)
{
    bx[x]=1;
    int i,j;
    for(i=1;i<=n;i++)if(!by[i])if(j=lx[x]+ly[i]-a[x][i])A=min(A,j);
    else
    {
        by[i]=1;
        if(!t[i]||find(t[i]))
        {
            t[i]=x;
            return 1;
        }
    }  
    return 0;
}
int ask(int x,int f,int X,int F,int Y)
{
    int i,j,k,l;
    for(i=h[x];i;i=ne[i])for(j=h[X];j;j=ne[j])if(p[i]!=f&&p[i]!=Y&&p[j]!=F)a1[p[i]][p[j]]=ask(p[i],x,p[j],X,Y);
    memset(a,0,sizeof(a));
    memset(ly,0,sizeof(ly));
    memset(lx,0,sizeof(lx));
    memset(t,0,sizeof(t));
    for(i=h[x],n=0;i;i=ne[i])if(p[i]!=f&&p[i]!=Y)n++;
    for(i=h[X],j=0;i;i=ne[i])if(p[i]!=F)j++;
    n=max(n,j);
    for(i=h[x],k=0;i;i=ne[i])if(p[i]!=f&&p[i]!=Y)for(k++,j=h[X],l=0;j;j=ne[j])if(p[j]!=F)a[k][++l]=a1[p[i]][p[j]];
    for(i=1;i<=n;i++)for(j=1;j<=n;j++)lx[i]=max(lx[i],a[i][j]);
    for(i=1;i<=n;i++)for(A=1000000000;;)
    {
        fill(bx+1,bx+n+1,0);
        fill(by+1,by+n+1,0);
        if(find(i))break;
        for(j=1;j<=n;j++)
        {
            if(bx[j])lx[j]-=A;
            if(by[j])ly[j]+=A;
        }
    }
    for(i=A=1;i<=n;i++)A+=lx[i]+ly[i];
    return A;
}
void work(int x,int f,int X,int F)
{
    for(int i=h[x];i;i=ne[i])if(p[i]!=f)work(p[i],x,X,F);
    ans=max(ans,ask(x,-1,X,F,X));
}
void dfs(int x,int f)
{
    if(~f)work(f,x,x,f);
    for(int i=h[x];i;i=ne[i])if(p[i]!=f)dfs(p[i],x);
}
class DeerInZooDivOne
{
    public:
        int getmax(vector <int> a, vector <int> b)
        {
            n=a.size()+1;
            for(i=0;i+1<n;i++)
            {
                p[++m]=b[i];
                ne[m]=h[a[i]];
                h[a[i]]=m;
                p[++m]=a[i];
                ne[m]=h[b[i]];
                h[b[i]]=m;
            }
            dfs(0,-1);
            return ans;
        }
};
