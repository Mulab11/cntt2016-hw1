#include<bits/stdc++.h>
using namespace std;
int n,m,s[50],i,j,ans;
class TheDevice
{
    public:
        int minimumAdditional(vector <string> plates)
        {
            n=plates.size();
            m=plates[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)s[j]+=plates[i][j]=='1';//求每一位上1的个数 
            for(i=0;i<m;i++)ans=max(ans,max(s[i]+1-n,0)+max(2-s[i],0));//计算答案 
            return ans;
        }
};