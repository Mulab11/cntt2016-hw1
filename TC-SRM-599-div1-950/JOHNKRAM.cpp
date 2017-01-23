#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
int c[2505][26],a[2505],i,j,k,n,m,N,M,h[55],ne[55],p[55],d[55],u[10],v[10],ans,s[7000],f[55][65536],g[65536];
vector<int> q[65536];
bool b[65536];
void dfs(int x,int f)
{
    if(a[x])
    {
        p[++m]=a[x];
        ne[m]=h[f];
        h[f]=m;
        f=a[x];
    }
    for(int i=0;i<26;i++)if(c[x][i])dfs(c[x][i],f);
}
void dfs(int x)
{
    int i,j;
    for(i=h[x];i;i=ne[i])dfs(p[i]);
    memset(g,0,sizeof(g));
    g[0]=1;
    for(i=h[x];i;i=ne[i])for(j=M-1;j;j--)for(k=q[j].size()-1;k;k--)g[s[j]]=(g[s[j]]+(ll)g[q[j][k]]*f[p[i]][s[j]^q[j][k]])%P;
    for(i=0;i<M;i++)
    {
        f[x][s[i]]=g[s[i]];
        if(x!=n+1)for(j=s[i];j;j^=j&-j)
        {
            f[x][s[i]]+=g[s[i]^(j&-j)];
            if(f[x][s[i]]>=P)f[x][s[i]]-=P;
        }
    }
}
class SimilarNames
{
    public:
        int count(vector <string> names, vector <int> info1, vector <int> info2)
        {
            n=names.size();
            a[N=1]=n+1;
            for(i=0;i<n;a[k]=++i)for(j=0,k=1;j<names[i].size();k=c[k][names[i][j++]-'a'])if(!c[k][names[i][j]-'a'])c[k][names[i][j]-'a']=++N;
            dfs(1,0);
            m=info1.size();
            for(i=N=0;i<m;i++)
            {
                d[N++]=info1[i];
                d[N++]=info2[i];
            }
            sort(d,d+N);
            N=unique(d,d+N)-d;
            for(i=0;i<N;i++)a[d[i]]=i;
            for(i=0;i<m;i++)
            {
                u[i]=a[info1[i]];
                v[i]=a[info2[i]];
            }
            for(i=0;i<1<<N;i++)
            {
                for(j=0;j<m;j++)if((i>>u[j]&1)&&!(i>>v[j]&1))break;
                if(j==m)b[s[M++]=i]=1;
            }
            for(i=0;i<M;i++)for(j=s[i];;j=s[i]&j-1)
            {
                if(b[j]&&b[s[i]^j])q[i].push_back(j);
                if(!j)break;
            }
            dfs(n+1);
            ans=f[n+1][(1<<N)-1];
            for(i=1;i+N<=n;i++)ans=(ll)ans*i%P;
            return ans;
        }
};
