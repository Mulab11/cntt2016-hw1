#include<bits/stdc++.h>
using namespace std;
string s;
int n,m,i,j,k,l,ans=1000000000,a[2],f[305][2];
class FlippingBitsDiv1
{
    public:
        int getmin(vector <string> S, int M)
        {
            for(i=0;i<S.size();i++)s+=S[i];
            n=s.size();
            m=n/M;
            bitset<300> t,T,d[20];
            if(m<M)
            {
                for(T=i=0;i<n;i++)T[i]=s[i]^'0';
                for(d[0]=j=0,i=1;i<=m;i++)for(d[i]=d[i-1];j<i*M&&j<n;j++)d[i][j]=1;
                for(i=0;i<1<<m;i++)
                {
                    t=T;
                    for(j=l=0;j<m;j++)if(i>>j&1)
                    {
                        l++;
                        t^=d[j+1];
                    }
                    for(j=0;j<M;j++)
                    {
                        for(a[0]=a[1]=0,k=j;k<n;k+=M)a[t[k]]++;
                        l+=min(a[0],a[1]);
                    }
                    ans=min(ans,l);
                }
            }
            else for(i=0;i<1<<M;i++)
            {
                for(f[f[0][0]=j=0][1]=1;j<m;j++)
                {
                    for(k=l=0;k<M;k++)l+=s[j*M+k]^(i>>k&1)^'0';
                    f[j+1][0]=min(f[j][0],f[j][1])+l;
                    f[j+1][1]=min(f[j][0]+2,f[j][1])+M-l;
                }
                for(k=l=0;j*M+k<n;k++)l+=s[j*M+k]^(i>>k&1)^'0';
                ans=min(ans,min(f[m][0],f[m][1])+l);
            }
            return ans;
        }
};
