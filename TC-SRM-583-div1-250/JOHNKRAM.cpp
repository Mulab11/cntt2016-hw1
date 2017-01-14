#include<bits/stdc++.h>
using namespace std;
int n,i,j,k,d[55][55];
int A(int x)
{
    if(x<0)return -x;
    return x;
}
class TravelOnMars
{
    public:
        int minTimes(vector <int> range, int startCity, int endCity)
        {
            n=range.size();
            memset(d,63,sizeof(d));
            for(i=0;i<n;i++)d[i][i]=0;
            for(i=0;i<n;i++)for(j=0;j<n;j++)if(i!=j&&min(A(i-j),n-A(i-j))<=range[i])d[i][j]=1;
            for(k=0;k<n;k++)for(i=0;i<n;i++)for(j=0;j<n;j++)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
            return d[startCity][endCity];
        }
};

