#include<bits/stdc++.h>
using namespace std;
int n,g[55][55],i,j,k,ans;
class Egalitarianism
{
    public:
        int maxDifference(vector <string> isFriend, int d)
        {
            n=isFriend.size();
            memset(g,63,sizeof(g));
            for(i=0;i<n;i++)g[i][i]=0;
            for(i=0;i<n;i++)for(j=0;j<n;j++)if(isFriend[i][j]=='Y')g[i][j]=1;
            for(k=0;k<n;k++)for(i=0;i<n;i++)for(j=0;j<n;j++)g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
            for(i=0;i<n;i++)for(j=0;j<n;j++)ans=max(ans,g[i][j]);
            if(ans==g[n][n])return -1;
            return ans*d;
        }
};
