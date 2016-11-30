#include<bits/stdc++.h>
using namespace std;
int n,i,j,k,d[55][55];
class ColorfulWolves
{
    public:
        int getmin(vector <string> colormap
        {
            n=colormap.size();
            memset(d,1,sizeof(d));
            for(i=0;i<n;i++)d[i][i]=0;
            for(i=0;i<n;i++)for(j=k=0;j<n;j++)if(colormap[i][j]=='Y')d[i][j]=k++;//计算i的后继是j的代价 
            for(k=0;k<n;k++)for(i=0;i<n;i++)for(j=0;j<n;j++)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);//Floyd求最小代价 
            if(d[0][n-1]==d[n][n])d[0][n-1]=-1;//判断是否无解 
            return d[0][n-1];
        }
};