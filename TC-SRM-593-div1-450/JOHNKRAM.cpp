#include<bits/stdc++.h>
using namespace std;
bool f[1000005];
int n,m,s,t,i,j,ans=1000000000;
class MayTheBestPetWin
{
    public:
        int calc(vector <int> A, vector <int> B)
        {
            n=A.size();
            for(f[i=0]=1;i<n;i++)
            {
                s+=A[i];
                t+=B[i];
                for(j=m;~j;j--)f[j+A[i]+B[i]]=f[j+A[i]+B[i]]||f[j];
                m+=A[i]+B[i];
            }
            for(i=0;i<=m;i++)if(f[i])ans=min(ans,max(t-i,i-s));
            return ans;
        }
};
