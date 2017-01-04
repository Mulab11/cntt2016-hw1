#include<bits/stdc++.h>
using namespace std;
int a[600][600];
class DrawingPointsDivOne
{
    public:
        int maxSteps(vector <int> x, vector <int> y)
        {
            int n=x.size(),i,j,k,l,r,m;
            for(i=0;i<n;i++)//处理坐标，去掉0.5和负数 
            {
                x[i]=x[i]*2+300;
                y[i]=y[i]*2+300;
            }
            l=0;
            r=140;
            while(l+1<r)//二分答案 
            {
                m=l+r>>1;
                memset(a,0,sizeof(a));
                for(i=0;i<n;i++)for(j=x[i]-m;j<=x[i]+m;j+=2)for(k=y[i]-m;k<=y[i]+m;k+=2)a[j][k]=1;//算出每个点是否被覆盖 
                for(i=160-m;i<441+m;i++)for(j=160-m;j<441+m;j++)a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];//二维前缀和 
                for(i=160,k=0;i<441;i++)for(j=160;j<441;j++)if(a[i+m][j+m]+a[i-m-1][j-m-1]-a[i+m][j-m-1]-a[i-m-1][j+m]==(m+1)*(m+1))k++;//求出m次操作后有多少个点 
                if(k==n)l=m;//判断m是否是合法答案 
                else r=m;
            }
            if(l==139)l=-1;//判断答案是否没有上界 
            return l;
        }
};