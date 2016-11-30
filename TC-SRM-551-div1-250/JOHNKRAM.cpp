#include<bits/stdc++.h>
using namespace std;
int n,i,j,k,l,ans,o,a[30][55];
class ColorfulChocolates
{
    public:
        int maximumSpread(string chocolates, int maxSwaps)
        {
            n=chocolates.size();
            for(i=0;i<n;i++)a[chocolates[i]-'A'][++a[chocolates[i]-'A'][0]]=i;//把巧克力按颜色分开 
            for(i=0;i<26;i++)//枚举并在一起的巧克力的颜色 
            {
                n=a[i][0];
                for(j=1;j<=n;j++)a[i][j]-=j;//数据处理 
                for(j=1;j<=n;j++)for(k=j;k<=n;k++)
                {
                    for(l=j,o=0;l<=k;l++)o+=max(a[i][l]-a[i][j+k>>1],a[i][j+k>>1]-a[i][l]);//计算第j块到第k块颜色为i的巧克力并在一起的最小移动次数 
                    if(o<=maxSwaps)ans=max(ans,k-j+1);//计算答案 
                    else break;
                }
            }
            return ans;
        }
};