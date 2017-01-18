#include<bits/stdc++.h>
using namespace std;
int N,n,m,i,j,u[55],v[55],l[55],s,ans;
string c;
bool b[55][55],g[55][55],d[55];
bool work(int x)
{
    for(int i=0;i<m;i++)if(g[x][i]&&!d[i])
    {
        d[i]=1;
        if(!~l[i]||work(l[i]))
        {
            l[i]=x;
            return 1;
        }
    }
    return 0;
}
void work(char x,char y)
{
    for(i=n=m=0;i<N;i++)if(c[i]==x)u[n++]=i;
    else if(c[i]==y)v[m++]=i;
    for(i=0;i<n;i++)for(j=0;j<m;j++)g[i][j]=b[u[i]][v[j]];
    memset(l,-1,sizeof(l));
    for(i=s=0;i<n;i++)
    {
        memset(d,0,sizeof(d));
        s+=work(i);
    }
    ans=min(ans,s);
}
class GearsDiv1
{
    public:
        int getmin(string color, vector <string> graph)
        {
            ans=N=color.size();
            c=color;
            for(i=0;i<N;i++)for(j=0;j<N;j++)b[i][j]=graph[i][j]=='Y';
            work('R','G');
            work('G','B');
            work('B','R');
            return ans;
        }
};
