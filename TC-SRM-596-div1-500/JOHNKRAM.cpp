#include<bits/stdc++.h>
using namespace std;
vector<long long> ans,z;
int n,i,j;
long long x,k;
class BitwiseAnd
{
    public:
        vector<long long> lexSmallest(vector<long long> subset, int N)
        {
            if(N>11)return z;
            n=subset.size();
            ans=subset;
            ans.resize(N);
            for(i=0;i<n;i++)for(j=i+1;j<n;j++)if(!(subset[i]&subset[j]))return z;
            else for(k=j+1;k<n;k++)if(subset[i]&subset[j]&subset[k])return z;
            for(i=0;i<n;x|=subset[i++]);
            for(i=0;i<n;i++)for(j=i+1;j<n;j++)
            {
                k=subset[i]&subset[j];
                subset[i]^=k;
                subset[j]^=k;
            }
            for(i=n;i<N;i++)
            {
                for(j=0;j<n;j++)
                {
                    if(!subset[j])return z;
                    ans[i]^=subset[j]&-subset[j];
                    subset[j]^=subset[j]&-subset[j];
                }
                for(j=i+1;j<N;j++)
                {
                    if((~x&-~x)==1LL<<60)return z;
                    ans[i]^=~x&-~x;
                    ans[j]^=~x&-~x;
                    x^=~x&-~x;
                }
            }
            sort(ans.begin(),ans.end());
            return ans;
        }
};
