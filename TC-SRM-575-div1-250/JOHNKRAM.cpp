#include<bits/stdc++.h>
using namespace std;
class TheNumberGameDivOne
{
    public:
        string find(long long n)
        {
            if(n&1)return "Brus";//奇数 
            for(int i=1;i<63;i+=2)if(1LL<<i==n)return "Brus";//2的奇数次幂 
            return "John";
        }
};