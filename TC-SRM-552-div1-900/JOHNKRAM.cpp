#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll N;
int n,m,i,j,p[100005];
bool b[1000005];
ll work(ll X,int x)//计算[1,X]内有多少个数可以用第[x+1,m]个质数的奇数次方相乘表示 
{
    if(x==m||p[x]>X)return 1;//边界情况 
    if((ll)p[x]*p[x+1]>X)return upper_bound(p+x,p+m,X)-p-x+1;//剪枝 
    ll s=work(X,x+1);//第x+1个质数没有出现 
    for(X/=p[x];X;X=X/p[x]/p[x])s+=work(X,x+1);//第x+1个质数出现了 
    return s;
}
class HolyNumbers
{
    public:
        long long count(long long upTo, int maximalPrime)
        {
            N=upTo;
            n=maximalPrime;
            for(i=2;i*i<=n;i++)if(!b[i])for(p[m++]=i,j=i*i;j<=n;j+=i)b[j]=1;//埃拉托色尼筛法预处理质数 
            for(;i<=n;i++)if(!b[i])p[m++]=i;
            return work(N,0);
        }
};