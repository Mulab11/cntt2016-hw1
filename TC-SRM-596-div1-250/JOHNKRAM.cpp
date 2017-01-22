#include<bits/stdc++.h>
using namespace std;
int o[1024],a[1024],i,j,ans;
class IncrementAndDoubling
{
    public:
        int getMin(vector <int> desiredArray)
        {
            for(i=1;i<1024;i++)o[i]=o[i>>1]+(i&1);
            for(i=2;i<1024;i++)a[i]=a[i>>1]+1;
            for(i=j=0;i<desiredArray.size();i++)
            {
                ans+=o[desiredArray[i]];
                j=max(j,desiredArray[i]);
            }
            return ans+a[j];
        }
};
