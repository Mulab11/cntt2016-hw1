#include<bits/stdc++.h>
using namespace std;
int w;
int work(int d,int n,int x)
{
    if((x==1||x==n)&&(n<=w||w==1)||x==n&&n%w==1||x==w&&n<w<<1)return 1;
    if(d==2)return 4;
    int ans=3,i,j;
    for(i=1;i*w<x;i++)for(j=1;j<=w;j++)ans=min(ans,work(d+1,n-i*j,x-i*j));
    for(i=1;i*w<x+w;i++)for(j=1;j<=(x-1)%w;j++)ans=min(ans,work(d+1,n-((i+(n-n%w)/w-(x+w-1)/w)*j+min(j,n%w)),x-i*j));
    for(i=1;i*w<x+w;i++)for(j=1;j+(x-1)%w<w;j++)ans=min(ans,work(d+1,n-((i+(n-n%w)/w-(x+w-1)/w)*j+min(j,max(0,n%w-x%w))),x+j-i*j));
    if(x+w<=n)ans=min(ans,work(d+1,(x+w-1)/w*w,x));
    return ans+1;
}
class FoxAndAvatar
{
    public:
        int minimalSteps(int n, int width, int x)
        {
            w=width;
            if(n==1)return 0;
            return work(0,n,x);
        }
};
