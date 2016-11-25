#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,ans,a[55];
bool g[55][55],b[55];
bool work(int x)//寻找增广路 
{
    b[x]=1;
    for(int i=1;i<=m;i++)if(g[x][i]&&(!a[i]||!b[a[i]]&&work(a[i])))
    {
        a[i]=x;
        return 1;
    }
    return 0;
}
class PointyWizardHats
{
    public:
        int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius)
        {
            n=topHeight.size();
            m=bottomHeight.size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)if(topRadius[i]<bottomRadius[j]&&topHeight[i]*bottomRadius[j]>topRadius[i]*bottomHeight[j])g[i+1][j+1]=1;//建图 
            for(i=1;i<=n;i++)//二分图最大匹配 
            {
                memset(b,0,sizeof(b));
                ans+=work(i);
            }
            return ans;
        }
};
