#include<bits/stdc++.h>
using namespace std;
int gcd(int x,int y)
{
    if(!y)return x;
    return gcd(y,x%y);
}
class PyramidSequences
{
    public:
        long long distinctPairs(int N, int M)
        {
            int g=gcd(--N,--M);
            N/=g;
            M/=g;
            return (long long)(g-1)*N*M+((long long)(N+1)*(M+1)+1>>1);
        }
};
