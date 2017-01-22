#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,k,l,f[2505],g[2505][2505];
long long ans;
string s;
class LittleElephantAndRGB
{
    public:
        long long getNumber(vector <string> list, int minGreen)
        {
            for(i=0;i<list.size();i++)s+=list[i];
            m=minGreen;
            n=s.size();
            for(i=n-1,j=0,k=n;~i;i--)
            {
                if(s[i]=='G')j++;
                else j=0;
                if(j>=m)
                {
                    j=m;
                    k=i+m-1;
                }
                else if(j)g[i][j]=k+1-i-j;
                f[i]=f[i+1]+n-k;
                for(l=1;l<m;l++)
                {
                    g[i][l]+=g[i+1][l];
                    if(l<j)g[i][l]++;
                }
            }
            for(i=0;i<n;i++)for(j=m-1;j;j--)g[i][j]+=g[i][j+1];
            for(i=0;i+1<n;i++)for(j=i,k=l=0;j+1<n;j++)
            {
                if(s[j]=='G')k++;
                else k=0;
                if(l|=k==m)ans+=(n-j)*(n-j-1)>>1;
                else ans+=f[j+1]+g[j+1][m-k];
            }
            return ans;
        }
};
