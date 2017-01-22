#include<bits/stdc++.h>
using namespace std;
int n,i,j;
bool b[10005];
long long ans=1;
class LittleElephantAndIntervalsDiv1
{
    public:
        long long getNumber(int M, vector <int> L, vector <int> R)
        {
            n=L.size();
            for(i=1;i<=M;i++)for(j=n-1;~j;j--)if(L[j]<=i&&R[j]>=i)
            {
                if(!b[j])ans<<=1;
                b[j]=1;
                break;
            }
            return ans;
        }
};
