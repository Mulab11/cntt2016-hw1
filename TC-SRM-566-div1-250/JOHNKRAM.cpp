#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,k,g[55][55],d[55];
long long ans;
class PenguinSledding
{
    public:
        long long countDesigns(int numCheckpoints, vector <int> checkpoint1, vector <int> checkpoint2)
        {
            n=numCheckpoints;
            m=checkpoint1.size();
            for(i=0;i<m;i++)
            {
                d[checkpoint1[i]]++;
                d[checkpoint2[i]]++;
                g[checkpoint1[i]][checkpoint2[i]]=g[checkpoint2[i]][checkpoint1[i]]=1;
            }
            for(i=3;i<=n;i++)for(j=2;j<i;j++)for(k=1;k<j;k++)ans+=g[i][j]&&g[j][k]&&g[k][i];//求三角形个数 
            for(i=1;i<=n;i++)ans+=(1LL<<d[i])-1;//求菊花图个数 
            return ans-m+1;
        }
};