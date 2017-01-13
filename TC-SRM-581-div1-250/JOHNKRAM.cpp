#include<bits/stdc++.h>
using namespace std;
int a[105],s[105],n,i,j,k,l,m,b[105];
string ans;
class SurveillanceSystem
{
    public:
        string getContainerInfo(string containers, vector <int> reports, int L)
        {
            n=containers.size();
            for(i=0;i<n;i++)a[i+1]=a[i]+(containers[i]=='X');
            for(i=0;i<reports.size();i++)s[reports[i]]++;
            for(i=0;i<=n;i++)for(j=0;j<n;j++)
            {
                for(k=l=m=0;k+L<=n;k++)if(a[k+L]==a[k]+i)
                {
                    l++;
                    m+=j>=k&&j<k+L;
                }
                if(s[i]&&m)b[j]=max(b[j],1);
                if(m+s[i]>l)b[j]=max(b[j],2);
            }
            for(i=0;i<n;i++)if(!b[i])ans+='-';
            else if(b[i]==1)ans+='?';
            else ans+='+';
            return ans;
        }
};

