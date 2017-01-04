#include<bits/stdc++.h>
using namespace std;
long long ans;
class AlternateColors2
{
    public:
        long long countWays(int n, int k)
        {
            if(k%3==1)ans=(long long)(n-k+2)*(n-k+1)>>1;//三种球都没取完 
            if(k%3==2)ans=1;//G=B，后面假设G>B 
            for(int i=0;i<k/3;i++)if(k-i*3&1)ans+=(n<<1)-k-i*3;//绿色球尚未取完 
            else ans+=k-i*3-1;//绿色球可能已取完 
            return ans;
        }
};