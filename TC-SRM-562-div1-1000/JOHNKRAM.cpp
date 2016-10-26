#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000009
int ans,n,m,i,j,x,y,l,h[50],ne[100],p[100],I[50],f[50],F[50][50][50][50],d[50][50],s[50][50],a[50][50],t[50][50];
bool b[50][50];
void dfs(int x,int fa)
{
    if(a[fa][x])return;
    a[fa][x]=s[fa][x]=1;
    for(int i=h[x];i;i=ne[i])if(p[i]!=fa)
    {
        dfs(p[i],x);
        s[fa][x]+=s[x][p[i]];
        a[fa][x]=(ll)a[fa][x]*a[x][p[i]]*I[s[x][p[i]]]%P;
    }
    a[fa][x]=(ll)a[fa][x]*f[s[fa][x]-1]%P;
}
void work(int x,int fa)
{
    if(b[fa][x])return;
    b[fa][x]=1;
    F[fa][x][0][0]=1;
    for(int i=h[x],j=0;i;i=ne[i])if(p[i]!=fa)
    {
        work(p[i],x);
        int a,b,c,d;
        memset(t,0,sizeof(t));
        for(a=0;a<=s[x][p[i]];a++)for(b=0;b<=s[x][p[i]];b++)for(c=0;c<=j;c++)for(d=0;d<=j;d++)t[a+c][b+d]=(t[a+c][b+d]+(ll)F[x][p[i]][a][b]*F[fa][x][c][d]*I[a]%P*I[b])%P;
        j+=s[x][p[i]];
        for(a=0;a<=j;a++)for(b=0;b<=j;b++)F[fa][x][a][b]=t[a][b];
    }
    int i,j;
    for(i=0;i<=s[fa][x];i++)for(j=0;j<=s[fa][x];j++)F[fa][x][i][j]=(ll)F[fa][x][i][j]*f[i]%P*f[j]%P;
    F[fa][x][0][s[fa][x]]=F[fa][x][s[fa][x]][0]=a[fa][x];
}
class InducedSubgraphs
{
    public:
        int getCount(vector<int> edge1,vector<int> edge2,int k)
        {
            for(I[1]=1,i=2;i<50;i++)I[i]=(ll)(P-P/i)*I[P%i]%P;
            for(i=f[0]=1;i<50;i++)f[i]=(ll)f[i-1]*i%P;
            for(i=I[0]=1;i<50;i++)I[i]=(ll)I[i]*I[i-1]%P;
            n=edge1.size()+1;
            if(k==1)return f[n];
            for(i=0;i<n;i++)for(j=i+1;j<n;j++)d[i][j]=d[j][i]=1000000000;
            for(i=0;i+1<n;i++)
            {
                d[edge1[i]][edge2[i]]=d[edge2[i]][edge1[i]]=1;
                p[++m]=edge2[i];
                ne[m]=h[edge1[i]];
                h[edge1[i]]=m;
                p[++m]=edge1[i];
                ne[m]=h[edge2[i]];
                h[edge2[i]]=m;
            }
            for(i=0;i<n;i++)dfs(i,n);
            for(l=0;l<n;l++)for(i=0;i<n;i++)for(j=0;j<n;j++)d[i][j]=min(d[i][j],d[i][l]+d[l][j]);
            if(k*2<=n)
            {
                for(i=0;i<n;i++)for(j=0;j<n;j++)if(d[i][j]==n-2*k+1)
                {
                    for(l=h[i];l;l=ne[l])if(d[p[l]][j]<d[i][j])break;
                    x=p[l];
                    for(l=h[j];l;l=ne[l])if(d[p[l]][i]<d[i][j])break;
                    y=p[l];
                    if(s[x][i]==k&&s[y][j]==k)ans=(ans+(ll)a[x][i]*a[y][j])%P;
                }
                return ans;
            }
            for(i=0;i<n;i++)work(i,n);
            for(i=0;i<n;i++)ans=(ans+F[n][i][n-k][n-k])%P;
            ans=(ll)ans*f[2*k-n-1]%P;
            return ans;
        }
};
