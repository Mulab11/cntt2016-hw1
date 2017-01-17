#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
int ans=1,n,x=2;
class TrafficCongestion
{
    public:
        int theMinCars(int treeHeight)
        {
            for(n=++treeHeight;n;n>>=1,x=(ll)x*x%P)if(n&1)ans=(ll)ans*x%P;
            return (ll)(ans+(treeHeight&1?1:-1))*333333336%P;
        }
};
