#include<bits/stdc++.h>
using namespace std;
int i,j,k,ans;
class BigFatInteger
{
    public:
        int minOperations(int A, int B)
        {
            for(i=2;i*i<=A;i++)if(A%i==0)
            {
                j++;
                for(k=0;A%i==0;A/=i)k++;
                ans=max(ans,(int)ceil(log2(k*B)));
            }
            if(A>1)
            {
                j++;
                k=1;
                ans=max(ans,(int)ceil(log2(k*B)));
            }
            return ans+j;
        }
};
