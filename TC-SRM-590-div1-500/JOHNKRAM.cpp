#include<bits/stdc++.h>
using namespace std;
class XorCards
{
    public:
        long long numberOfWays(vector<long long> number, long long limit)
        {
            int n=number.size(),i,j,k;
            long long ans,s;
            for(i=49,j=0;~i;i--)
            {
                for(k=j;k<n&&!(number[k]>>i&1);k++);
                if(k==n)continue;
                swap(number[j],number[k]);
                for(k=0;k<n;k++)if(j!=k&&(number[k]>>i&1))number[k]^=number[j];
                j++;
            }
            for(i=ans=s=0;i<n;i++)if((s^number[i])<=limit)
            {
                s^=number[i];
                ans|=1LL<<n-i-1;
            }
            return ans+1;
        }
};
