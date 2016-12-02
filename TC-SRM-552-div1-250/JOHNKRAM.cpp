#include<bits/stdc++.h>
using namespace std;
class FoxPaintingBalls
{
    public:
        long long theMax(long long R, long long G, long long B, int N)
        {
            if(N==1)return R+G+B;//N=1特判 
            long long X=(long long)N*(N+1)/6,S=min(min(R,G),B)/X;//X等于每个三角形每种颜色最少个数 
            if(N%3==1)S=min(S,(R+G+B)/(3*X+1));//N%3==1时每个三角形有一种颜色多一个，推一推式子可以得出一个新的不等式 
            return S;
        }
};