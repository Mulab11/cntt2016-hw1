#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000009
string c1,c2;
int n,i,j,c[1300],f[1300],I[1300],d[1300][1300],s[1300],a[3600][1300];
class ColorfulBuilding
{
    public:
        int count(vector <string> color1, vector <string> color2, int L)
        {
            for(i=0;i<color1.size();i++)c1+=color1[i];
            for(i=0;i<color2.size();i++)c2+=color2[i];
            n=c1.size();
            for(i=0;i<n;i++)c[i+1]=(c1[i]-'A')*60+c2[i]-'A';
            for(I[0]=I[1]=f[0]=f[1]=1,i=2;i<n;i++)
            {
                f[i]=(ll)f[i-1]*i%P;
                I[i]=(ll)(P-P/i)*I[P%i]%P;
            }
            for(i=1;i<=n;i++)for(j=1;j<=i;j++)
            {
                d[i][j]=a[c[i]][j];
                if(j==1)d[i][j]+=f[n-1];
                else d[i][j]+=s[j-1]-a[c[i]][j-1];
                if(d[i][j]<0)d[i][j]+=P;
                s[j]+=d[i][j]=(ll)d[i][j]*I[n-i]%P;
                if(s[j]>=P)s[j]-=P;
                a[c[i]][j]+=d[i][j];
                if(a[c[i]][j]>=P)a[c[i]][j]-=P;
            }
            return d[n][L];
        }
};
