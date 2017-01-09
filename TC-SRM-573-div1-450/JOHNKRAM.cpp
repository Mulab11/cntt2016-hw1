#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,i,j,k,l;
bool b[55][55];
ll d[55][55],ans;
ll A(ll x)//求绝对值 
{
    if(x<0)return -x;
    return x;
}
class SkiResorts
{
    public:
        long long minCost(vector <string> road, vector <int> altitude)
        {
            n=road.size();
            memset(d,127,sizeof(d));
            ans=d[n][n];
            for(i=0;i<n;i++)d[0][i]=A(altitude[i]-altitude[0]);//初始n个点的距离 
            for(;;)//Dijkstra求最短路 
            {
                for(i=0,k=-1;i<n;i++)for(j=0;j<n;j++)if(!b[i][j]&&(!~k||d[i][j]<d[k][l]))
                {
                    k=i;
                    l=j;
                }
                if(!~k||d[k][l]==d[n][n])break;
                b[k][l]=1;
                for(i=0;i<n;i++)for(j=0;j<n;j++)if(road[k][i]=='Y'&&altitude[l]>=altitude[j])d[i][j]=min(d[i][j],d[k][l]+A(altitude[i]-altitude[j]));
            }
            for(i=0;i<n;i++)ans=min(ans,d[n-1][i]);//计算答案 
            if(ans==d[n][n])ans=-1;//判断无解 
            return ans;
        }
};