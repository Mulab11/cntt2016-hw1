#include<bits/stdc++.h>
using namespace std;
struct edge
{
    int u,v,w;
}e[10000];
int m,N,i,j,k,in[10005],p[10005],d[10005],ans,b[10005];
string s;
class FoxTheLinguist
{
    public:
        int minimalHours(int n, vector <string> courseInfo)
        {
            for(i=0;i<courseInfo.size();i++)s+=courseInfo[i];
            for(i=0;i<s.size();i+=12)
            {
                e[++m].u=(s[i+1]-'0')*n+s[i]-64;
                e[m].v=(s[i+5]-'0')*n+s[i+4]-64;
                e[m].w=(s[i+7]-'0')*1000+(s[i+8]-'0')*100+(s[i+9]-'0')*10+s[i+10]-'0';
            }
            for(i=1;i<=n;i++)for(j=0;j<9;j++)
            {
                e[++m].u=(j+1)*n+i;
                e[m].v=j*n+i;
                e[m].w=0;
            }
            for(i=1;i<=n;i++)
            {
                e[++m].u=0;
                e[m].v=i;
                e[m].w=0;
            }
            n=n*10+1;
            for(;;)
            {
                fill(in,in+n,1000000000);
                in[0]=0;
                for(i=1;i<=m;i++)if(e[i].u!=e[i].v&&e[i].w<in[e[i].v])
                {
                    in[e[i].v]=e[i].w;
                    p[e[i].v]=e[i].u;
                }
                for(i=1;i<n;i++)if(in[i]==1000000000)return -1;
                N=1;
                fill(b,b+n,-1);
                fill(d,d+n,-1);
                for(d[0]=i=0;i<n;i++)
                {
                    ans+=in[i];
                    for(j=i;j&&!~d[j]&&b[j]!=i;j=p[j])b[j]=i;
                    if(j&&!~d[j])
                    {
                        for(k=p[j];k!=j;k=p[k])d[k]=N;
                        d[j]=N++;
                    }
                }
                if(N==1)return ans;
                for(i=0;i<n;i++)if(!~d[i])d[i]=N++;
                for(i=1;i<=m;i++)
                {
                    e[i].w-=in[e[i].v];
                    e[i].u=d[e[i].u];
                    e[i].v=d[e[i].v];
                }
                n=N;
            }
        }
};
