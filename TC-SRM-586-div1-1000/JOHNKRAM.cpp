#include<bits/stdc++.h>
using namespace std;
int n,i,j,k,l,m,x,y,z,ans=1000000000,f[105][30][30];
class StringWeight
{
    public:
        int getMinimum(vector <int> L)
        {
            n=L.size();
            memset(f,63,sizeof(f));
            for(i=f[0][0][0]=0;i<n;i++)for(j=0;j<27;j++)for(k=0;j+k<27;k++)for(l=0;k+l<27;l++)for(m=max(0,min(L[i],26)-j)-l;j+k+l+m<27;m++)
            {
                x=min(j,l);
                y=j-x;
                z=x+m;
                f[i+1][j+m][k+l]=min(f[i+1][j+m][k+l],f[i][j][k]+(x*(x+1)>>1)+y*L[i]+!y*max(0,L[i]-26)+(z*(z-1)>>1));
            }
            return f[n][0][26];
        }
};
