#include<bits/stdc++.h>
using namespace std;
int n,i,m,M,N,h[100],ne[2500],p[2500],l[50],r[50],a[50],c[100];
bool b[50];
void add(int u,int v)
{
    if(!~u)u=n<<1;
    if(!~v)v=n<<1;
    p[++M]=v;
    ne[M]=h[u];
    h[u]=M;
    p[++M]=u;
    ne[M]=h[v];
    h[v]=M;
}
bool dfs(int x)//二分图染色 
{
    for(int i=h[x];i;i=ne[i])if(!~c[p[i]])
    {
        c[p[i]]=!c[x];
        if(!dfs(p[i]))return 0;
    }
    else if(c[p[i]]==c[x])return 0;
    return 1;
}
bool dfs(int x,int y)//算法1 
{
    if(x==n<<1)
    {
        int i,j;
        memset(h,0,sizeof(h));
        for(i=M=0;i<n;i++)for(j=0;j<n;j++)if(max(l[i],l[j])<min(r[i],r[j])&&(l[i]>l[j])==(r[i]>=r[j]))add(i,j);//建图 
        memset(c,-1,sizeof(c));
        for(i=0;i<n;i++)if(!~c[i])
        {
            c[i]=0;
            if(!dfs(i))return 0;//判断是否有解 
        }
        return 1;
    }
    if(b[x])return dfs(x+1,y);
    b[l[a[y]]=x]=1;
    for(int i=x+1;i<n<<1;i++)if(!b[i])//枚举第一个没有选到的点与哪个点配对 
    {
        b[r[a[y]]=i]=1;
        if(dfs(x+1,y+1))return 1;
        b[i]=0;
    }
    b[x]=0;
    return 0;
}
bool work(int x)//算法2 
{
    if(x==n)
    {
        int i,j;
        for(i=0;i<n;i++)if(~l[i])for(j=0;j<n;j++)if(~l[j]&&max(l[i],l[j])<min(r[i],r[j])&&(l[i]>l[j])==(r[i]>=r[j])&&b[i]==b[j])return 0;//判断上下情况是否合法 
        memset(h,0,sizeof(h));
        for(i=M=0,N=(n<<1)+1;i<n;i++)if(~l[i])//建图 
        {
            if(!b[i]&&!((r[i]^l[i])&1))add(r[i]-1,l[i]);
            else
            {
                add(l[i],N);
                add(r[i]-1,N++);
            }
            if(b[i])
            {
                add(l[i],l[i]-1);
                add(r[i],r[i]-1);
            }
            else
            {
                add(l[i],N);
                add(l[i]-1,N++);
                add(r[i],N);
                add(r[i]-1,N++);
            }
        }
        add(-1,N);
        add((n<<1)-1,N++);
        memset(c,-1,sizeof(c));
        for(i=0;i<N;i++)if(!~c[i])
        {
            c[i]=0;
            if(!dfs(i))return 0;//判断是否有解 
        }
        return 1;
    }
    if(!~l[x])return work(x+1);
    b[x]=0;//半圆朝上 
    if(work(x+1))return 1;
    b[x]=1;//半圆朝下 
    return work(x+1);
}
class DisjointSemicircles
{
    public:
        string getPossibility(vector <int> labels)
        {
            n=labels.size();
            memset(l,-1,sizeof(l));
            memset(r,-1,sizeof(r));
            for(i=0;i<n;i++)if(~labels[i])
            {
                b[i]=1;
                if(~l[labels[i]])r[labels[i]]=i;
                else l[labels[i]]=i;
            }
            n>>=1;
            for(i=m=0;i<n;i++)if(!~l[i])a[m++]=i;
            if(m<=6)return dfs(0,0)?"POSSIBLE":"IMPOSSIBLE";//情况1 
            else return work(0)?"POSSIBLE":"IMPOSSIBLE";//情况2 
        }
};