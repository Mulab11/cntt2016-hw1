#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,k,p[100005],a[1000005],s[100005],x[1000005];
bool b[100005];
long long ans;
class TheDivisionGame
{
    public:
        long long countWinningIntervals(int L, int R)
        {
            for(n=1;n*n<R;n++);//求sqrt(R) 
            for(i=2;i<=n;i++)//线性筛求所有<=sqrt(R)的质数 
            {
                if(!b[i])p[m++]=i;
                for(j=0;j<m&&i*p[j]<=n;j++)
                {
                    b[i*p[j]]=1;
                    if(i%p[j]==0)break;
                }
            }
            for(i=0;i+L<=R;i++)x[i]=i+L;
            for(i=0;i<m;i++)for(j=(L+p[i]-1)/p[i]*p[i];j<=R;j+=p[i])for(;x[j-L]%p[i]==0;x[j-L]/=p[i])a[j-L]++;//求质因子数 
            for(i=0;i+L<=R;i++)a[i]+=x[i]>1;
            for(s[i=j=0]=1;i+L<=R;i++)ans+=s[j^=a[i]]++;//计算答案 
            return (long long)(R-L+2)*(R-L+1)/2-ans;
        }
};