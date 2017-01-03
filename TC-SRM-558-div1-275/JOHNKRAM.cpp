#include<bits/stdc++.h>
using namespace std;
int f[55],n,a[55],i,j,k,l,ans=1000000000;
class Stamp
{
    public:
        int getMinimumCost(string desiredColor, int stampCost, int pushCost)
        {
            n=desiredColor.size();
            for(i=0;i<n;i++)if(desiredColor[i]=='R')a[i+1]=1;//将颜色转换成数字 
            else if(desiredColor[i]=='G')a[i+1]=2;
            else if(desiredColor[i]=='B')a[i+1]=4;
            else a[i+1]=7;
            for(i=1;i<=n;i++)//枚举长度 
            {
                f[0]=0;
                for(j=1;j<=n;j++)for(k=j-1,l=a[j],f[j]=1000;(~k)&&l;k--)
                {
                    if(j>=i+k)f[j]=min(f[j],f[k]+(j-k+i-1)/i);//DP计算最小次数 
                    l&=a[k];//利用按位与判断能否使用同一种颜色 
                }
                ans=min(ans,i*stampCost+f[n]*pushCost);//计算答案 
            }
            return ans;
        }
};