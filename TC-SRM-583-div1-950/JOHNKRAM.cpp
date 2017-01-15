#include<bits/stdc++.h>
using namespace std;
int n,m,x,i,j,k,l,o[4096],a[25][25],f[4096],s,b[25],c[25],d[25];
double ans;
class RandomPaintingOnABoard
{
    public:
        double expectedSteps(vector <string> prob)
        {
            n=prob.size();
            m=prob[0].size();
            if(n<=m)for(i=0;i<n;i++)for(j=0;j<m;j++)a[i][j]=prob[i][j]^'0';
            else
            {
                for(i=0;i<n;i++)for(j=0;j<m;j++)a[j][i]=prob[i][j]^'0';
                swap(n,m);
            }
            for(i=0;i<n;i++)for(j=0;j<m;j++)
            {
                s+=a[i][j];
                b[i]+=a[i][j];
                c[j]+=a[i][j];
            }
            for(o[i=0]=-1;i<1<<n;i++)
            {
                o[i]=o[i>>1];
                if(i&1)o[i]=-o[i];
                for(j=0;j<m;j++)d[j]=c[j];
                for(j=x=0;j<n;j++)if(i>>j&1)for(x+=b[j],k=0;k<m;k++)d[k]-=a[j][k];
                memset(f,0,sizeof(f));
                for(f[j=k=0]=1;j<m;j++)for(l=k+=d[j];l>=d[j];l--)f[l]-=f[l-d[j]];
                for(j=0;j<=k;j++)if(j+x)ans+=(double)o[i]*f[j]*s/(j+x);
            }
            return ans;
        }
};
