#include<bits/stdc++.h>
using namespace std;
int n,i,j,k,m,ans;
class EelAndRabbit
{
    public:
        int getmax(vector <int> l, vector <int> t)
        {
            n=l.size();
            for(i=0;i<n;i++)for(j=i;j<n;j++)
            {
                for(k=m=0;k<n;k++)if(t[i]>=t[k]&&t[i]<=t[k]+l[k]||t[j]>=t[k]&&t[j]<=t[k]+l[k])m++;
                ans=max(ans,m);
            }
            return ans;
        }
};
