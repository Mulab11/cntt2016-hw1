#include<bits/stdc++.h>
using namespace std;
int n,i,j,ans,a[55];
class TheTree
{
    public:
        int maximumDiameter(vector <int> cnt)
        {
            n=cnt.size();
            for(i=0;i<n;i++)a[i+1]=cnt[i];
            for(a[0]=1,i=n,j=n+1;~i;i--)
            {
                ans=max(ans,n+j-(i<<1)-1);
                if(a[i]==1)j=i;
            }
            return ans;
        }
};
