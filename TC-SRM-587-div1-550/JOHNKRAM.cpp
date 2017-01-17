#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
ll x;
int i;
ld ans;
class TriangleXor
{
    public:
        int theArea(int W)
        {
            ans=(ll)W*(W+1)>>1;
            for(i=1;i<=W;i++)
            {
                x=(ll)W*W*(W-i+1);
                if(i&1)ans-=(ld)x/(W+i);
                else ans+=(ld)x/(W+i);
            }
            return ans;
        }
};
