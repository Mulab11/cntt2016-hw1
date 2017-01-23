#include<bits/stdc++.h>
using namespace std;
int n,i,j,ans,f[55],d[55];
bool b[55][55];
void dfs(int x)
{
    int i=0,j=d[x]=0;
    for(;i<=n;i++)if(b[x][i]&&i!=f[x])
    {
        f[i]=x;
        dfs(i);
        if(d[i])d[x]+=d[i];
        else
        {
            d[x]+=j;
            j=1;
        }
    }
}
class TPS
{
    public:
        int minimalBeacons(vector <string> linked)
        {
            ans=n=linked.size();
            if(n==1)return 0;
            for(i=0;i<n;i++)for(j=0;j<n;j++)b[i+1][j+1]=linked[i][j]=='Y';
            for(i=1;i<=n;i++)
            {
                f[i]=0;
                dfs(i);
                ans=min(ans,d[i]+1);
            }
            return ans;
        }
};
