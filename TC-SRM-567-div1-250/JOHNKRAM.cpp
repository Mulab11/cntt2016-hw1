#include<bits/stdc++.h>
using namespace std;
int a[100000],b[100000],i,j,ans;
class TheSquareRootDilemma
{
    public:
        int countPairs(int N, int M)
        {
            for(i=1;i<=N;i++)a[i]=i;
            for(i=1;i<<2<=N;i++)if(a[i]==i)for(j=1;i*j*j<=N;j++)a[i*j*j]=i;//求最大无平方因子 
            for(i=1;i<=M;i++)//求sqrt(i)下取整 
            {
                b[i]=b[i-1];
                if((b[i]+1)*(b[i]+1)==i)b[i]++;
            }
            for(i=1;i<=N;i++)ans+=b[M/a[i]];//计算答案 
            return ans;
        }
};