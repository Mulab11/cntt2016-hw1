#include<bits/stdc++.h>
using namespace std;
#define ll long long
int f[55][55],i,j,k,l,n,m,ans;
ll a[55],b[55];
class AstronomicalRecords
{
    public:
        int minimalPlanets(vector <int> A, vector <int> B)
        {
            n=A.size();
            m=B.size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)
            {
                for(k=0;k<n;k++)a[k+1]=(ll)A[k]*B[j];
                for(k=0;k<m;k++)b[k+1]=(ll)B[k]*A[i];
                for(k=1;k<=n;k++)for(l=1;l<=m;l++)
                {
                    f[k][l]=max(f[k-1][l],f[k][l-1]);
                    if(a[k]==b[l])f[k][l]=max(f[k][l],f[k-1][l-1]+1);
                }
                ans=max(ans,f[n][m]);
            }
            return n+m-ans;
        }
};
