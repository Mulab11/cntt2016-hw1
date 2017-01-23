#include<bits/stdc++.h>
using namespace std;
long long n,N,i,j,k,l,m,o,p,ans,f[1000005],g[1000005],h[1000005];
class SparseFactorial
{
    public:
        long long getCount(long long lo, long long hi, long long divisor)
        {
            for(n=divisor,i=2,N=1;divisor>1;i++)if(divisor%i==0)
            {
                for(j=1,k=0;divisor%i==0;j*=i,k++,divisor/=i);
                fill(g,g+j,1LL<<60);
                fill(h,h+j,0);
                for(l=0;l<i*k;l++)for(o=(m=l*l)%i;o<j;o+=i)if(g[o]==1LL<<60)
                {
                    for(p=(o+j-m%j)%j;p&&p%i==0;p/=i,h[o]++);
                    if(!p||h[o]>=k)g[o]=m+1;
                }
                for(k=N*j-1;~k;k--)f[k]=max(f[k%N],g[k%j]);
                N*=j;
            }
            for(lo--,i=0;i<n;i++)
            {
                f[i]=(f[i]+n-i-1)/n*n+i;
                ans+=max((hi+n-f[i])/n,0LL)-max((lo+n-f[i])/n,0LL);
            }
            return ans;
        }
};
