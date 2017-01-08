#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll d[80][80][2],g[2][80],ans;
int n,i,m,h[80],ne[80],p[80];
bool b[80];
void dfs(int x,int f)//树形DP 
{
    b[x]=0;
    int i,j,k,l,u,v;
    for(i=h[x];i;i=ne[i])if(p[i]!=f)dfs(p[i],x);
    for(i=0;i<2;i++)for(j=0;j<2;j++)
    {
        memset(g[0],0,sizeof(g[0]));
        if(j)g[0][n]=1;//初始状态 
        else g[0][n-1+(i<<1)]=1;
        for(k=h[x],l=1;k;k=ne[k])if(p[k]!=f)
        {
            memset(g[l],0,sizeof(g[l]));
            for(u=0;u<=n<<1;u++)if(d[p[k]][u][j])for(v=0;v<=n<<1;v++)if(g[!l][v])g[l][u+v-n]+=d[p[k]][u][j]*g[!l][v];//状态转移 
            l=!l;
        }
        for(k=0;k<=n<<1;k++)d[x][k][i]+=g[!l][k];//计算方案数 
    }
}
class CentaurCompany
{
    public:
        double getvalue(vector <int> a, vector <int> b)
        {
            n=a.size()+1;
            for(i=0;i+1<n;i++)
            {
                p[++m]=a[i];
                ne[m]=h[b[i]];
                h[b[i]]=m;
                p[++m]=b[i];
                ne[m]=h[a[i]];
                h[a[i]]=m;
            }
            dfs(1,0);
            for(i=0;i+1<n;i++)ans+=i*d[1][i+n+2][1];//计算答案 
            return (double)ans/(1LL<<n-1);
        }
};