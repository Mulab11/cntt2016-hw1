#include<bits/stdc++.h>
using namespace std;
class XorAndSum
{
    public:
        long long maxSum(vector<long long> number)
        {
            int n=number.size(),i,j,k;
            long long ans=0;
            for(i=49,j=0;~i;i--)//求线性基 
            {
                for(k=j;k<n&&!(number[k]>>i&1);k++);
                if(k==n)continue;
                swap(number[j],number[k]);
                for(k=0;k<n;k++)if(j!=k&&(number[k]>>i&1))number[k]^=number[j];
                j++;
            }
            for(i=1;i<n;i++)number[0]^=number[i];
            for(ans=number[0],i=1;i<n;i++)ans+=number[i]^number[0];//计算答案 
            return ans;
        }
};