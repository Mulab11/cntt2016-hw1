#include<bits/stdc++.h>
using namespace std;
long long f[55][105];
int n,i,j;
class MonstersValley
{
    public:
        int minimumPrice(vector<long long> dread, vector <int> price)
        {
            n=dread.size();
            memset(f,128,sizeof(f));
            for(f[0][0]=0,i=1;i<=n;i++)for(j=1;j<=i<<1;j++)
            {
                f[i][j]=f[i][j-1];
                if(j>=price[i-1])f[i][j]=max(f[i][j],f[i-1][j-price[i-1]]+dread[i-1]);//打死第i只怪兽 
                if(f[i-1][j]>=dread[i-1])f[i][j]=max(f[i][j],f[i-1][j]);//不打第i只怪兽 
            }
            for(i=1;;i++)if(f[n][i]>0)break;//计算答案 
            return i;
        }
};