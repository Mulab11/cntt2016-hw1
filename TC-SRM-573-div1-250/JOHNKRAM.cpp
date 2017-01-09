#include<bits/stdc++.h>
using namespace std;
int n,i,x,a[100],ans;
class TeamContest
{
    public:
        int worstRank(vector <int> strength)
        {
            n=strength.size()-3;
            x=max(max(strength[0],strength[1]),strength[2])+min(min(strength[0],strength[1]),strength[2])+1;
            for(i=0;i<n;i++)a[i]=strength[i+3];
            sort(a,a+n);
            for(i=0;--n;i+=2,ans++)//贪心求解 
            {
                for(;i<n&&a[i]+a[n]<x;i++);//求区间左端点 
                if(i+2>n)return ans+1;
            }
        }
};