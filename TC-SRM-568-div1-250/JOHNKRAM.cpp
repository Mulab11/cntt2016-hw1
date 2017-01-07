#include<bits/stdc++.h>
using namespace std;
int n,i,j,k,ans=1000000000,s[55],S;
class BallsSeparating
{
    public:
        int minOperations(vector <int> red, vector <int> green, vector <int> blue)
        {
            n=red.size();
            if(n<3)return -1;
            for(i=0;i<n;i++)S+=s[i]=red[i]+green[i]+blue[i]-max(max(red[i],green[i]),blue[i]);//计算第i个盒子保留一种颜色的最小移动次数 
            for(i=0;i<n;i++)for(j=0;j<n;j++)if(i!=j)for(k=0;k<n;k++)if(k!=i&&k!=j)ans=min(ans,S-s[i]-s[j]-s[k]+green[i]+blue[i]+red[j]+blue[j]+red[k]+green[k]);//枚举红、绿、蓝三色球移动到的盒子 
            return ans;
        }
};