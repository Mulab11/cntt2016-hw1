#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
int n,i,j,k,ans,N,I[100005],C[100005];
int A(int x)//求绝对值 
{
    if(x<0)return -x;
    return x;
}
int work(vector<int> a)
{
    for(i=0;i<n;i++)if((a[i]^a[0])&1)return 0;//判断能否到同一个点上 
    for(i=a[ans=0]-N;i<=a[0]+N;i+=2)//枚举终点 
    {
        for(j=0,k=1;j<n;j++)if(A(a[j]-i)<=N)k=(ll)k*C[N-A(a[j]-i)>>1]%P;//计算方案数 
        else
        {
            k=0;
            break;
        }
        ans+=k;//计算答案 
        if(ans>=P)ans-=P;
    }
    return ans;
}
class WolfPack
{
    public:
        int calc(vector <int> x, vector <int> y, int m)
        {
            n=x.size();
            N=m;
            for(I[1]=1,i=2;i<=m;i++)I[i]=(ll)(P-P/i)*I[P%i]%P;//预处理逆元 
            for(C[0]=i=1;i<=m;i++)C[i]=(ll)C[i-1]*(m-i+1)%P*I[i]%P;//预处理组合数 
            for(i=0;i<n;i++)//坐标变换 
            {
                j=x[i]-y[i];
                x[i]+=y[i];
                y[i]=j;
            }
            return (ll)work(x)*work(y)%P;
        }
};