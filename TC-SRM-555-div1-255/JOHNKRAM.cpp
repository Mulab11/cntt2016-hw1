#include<bits/stdc++.h>
using namespace std;
#define ll long long
bool check(ll x)//判断是否是5的次幂 
{
    if(!x)return 0;
    for(;x>1;x/=5)if(x%5)return 0;
    return 1;
}
class CuttingBitString
{
    public:
        int getmin(string S)
        {
            int n=S.size(),i,j,f[100];
            ll a[100];
            for(a[0]=0,i=1;i<=n;i++)a[i]=(a[i-1]<<1)^S[i-1]^'0';//计算前i位组成的二进制数是多少 
            for(f[0]=0,i=1;i<=n;i++)for(f[i]=n+1,j=0;j<i;j++)if(f[j]<n&&S[j]=='1'&&check(a[i]^(a[j]<<i-j)))f[i]=min(f[i],f[j]+1);//计算答案 
            if(f[n]==n+1)f[n]=-1;
            return f[n];
        }
};