#include<bits/stdc++.h>
using namespace std;
int n,i,j,a[3000],s;
double t=1,ans;
class TheSwapsDivOne
{
    public:
        double find(vector <string> sequence, int k)
        {
            for(i=0;i<sequence.size();i++)for(j=0;j<sequence[i].size();j++)s+=a[n++]=sequence[i][j]^'0';
            for(i=0;i<k;i++)t=t*(n-3)/(n-1);//求x[k] 
            for(i=0;i<n;i++)ans+=(t*a[i]+(1-t)*s/n)*(i+1)*(n-i);//计算答案 
            return ans*2/n/(n+1);
        }
};