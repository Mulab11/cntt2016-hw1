#include<bits/stdc++.h>
using namespace std;
int n,m,M,i,j,k,l,s,t,h[2505],ne[10005],p[10005],d[2505],f[2505],g[2505];
void add(int u,int v)
{
    p[++M]=v;
    ne[M]=h[u];
    h[u]=M;
    p[++M]=u;
    ne[M]=h[v];
    h[v]=M;
}
void dfs(int x)
{
    g[x]=1;
    for(int i=h[x];i;i=ne[i])if(p[i]!=f[x])
    {
        f[p[i]]=x;
        d[p[i]]=d[x]+1;
        dfs(p[i]);
        g[x]=max(g[x],g[p[i]]+1);
    }
}
class GameInDarknessDiv1
{
    public:
        string check(vector <string> field)
        {
            n=field.size();
            m=field[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)if(field[i][j]!='#')
            {
                if(field[i][j]=='A')s=i*m+j;
                if(field[i][j]=='B')t=i*m+j;
                if(i&&field[i-1][j]!='#')add((i-1)*m+j,i*m+j);
                if(j&&field[i][j-1]!='#')add(i*m+j-1,i*m+j);
            }
            for(i=0;i<n;i++)for(j=0;j<m;j++)if(field[i][j]!='#')
            {
                d[i*m+j]=0;
                f[i*m+j]=-1;
                dfs(i*m+j);
                for(k=h[i*m+j],l=0;k;k=ne[k])if(g[p[k]]>2)l++;
                if(l>2&&d[s]>d[t]+1)return "Bob wins";
            }
            return "Alice wins";
        }
};
