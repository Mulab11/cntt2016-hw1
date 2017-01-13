#include<bits/stdc++.h>
using namespace std;
struct node
{
    int a,b;
    bool operator<(const node& y)const
    {
        if(a==y.a)return b<y.b;
        return a<y.a;
    }
}a[10000];
int n,i,j,l,r,d1[10000],d2[10000],f[10000],q[10000],he,ta;
void bfs(int s,int *d)
{
    fill(d+1,d+n+1,-1);
    he=ta=0;
    d[q[ta++]=s]=0;
    for(;he!=ta;)for(i=q[he++],j=1;j<=n;j++)if(!~d[j]&&max(a[i].a,a[j].a)<=min(a[i].b,a[j].b))d[q[ta++]=j]=d[i]+1;
}
class ShoutterDiv1
{
    public:
        int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1)
        {
            for(i=0;i<s1000.size();i++)for(j=0;j<s1000[i].size();j++)
            {
                a[++n].a=(s1000[i][j]^'0')*1000+(s100[i][j]^'0')*100+(s10[i][j]^'0')*10+(s1[i][j]^'0')*1;
                a[n].b=(t1000[i][j]^'0')*1000+(t100[i][j]^'0')*100+(t10[i][j]^'0')*10+(t1[i][j]^'0')*1;
            }
            if(n==1)return 0;
            sort(a+1,a+n+1);
            for(i=l=r=1;i<=n;i++)
            {
                if(a[i].b<a[l].b)l=i;
                if(a[i].a>a[r].a)r=i;
            }
            bfs(l,d1);
            bfs(r,d2);
            for(i=1;i<=n;i++)if(!~d1[i]||!~d2[i])return -1;
            else f[i]=max(d1[i]-1,0)+max(d2[i]-1,0);
            for(i=1;i<=n;i++)for(j=1;j<=n;j++)if(a[i].a<=a[j].a&&a[i].b>=a[j].b)f[j]=min(f[j],f[i]+1);
            for(i=1,j=0;i<=n;i++)j+=f[i];
            return j;
        }
};
