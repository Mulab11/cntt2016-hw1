#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 500001
#define M 20001
#define pb push_back
bool p2[N],p3[N];
int mu[N],i,j,k;
vector<int> a[M],b[M];
ll s2(ll x)
{
    ll l=1,r=x+1,m;
    while(l+1<r)
    {
        m=l+r>>1;
        if(x/m/m)l=m;
        else r=m;
    }
    return l;
}
ll s3(ll x)
{
    ll l=1,r=x+1,m;
    while(l+1<r)
    {
        m=l+r>>1;
        if(x/m/m/m)l=m;
        else r=m;
    }
    return l;
}
ll gcd(ll x,ll y)
{
    if(!y)return x;
    return gcd(y,x%y);
}
ll work(ll n)
{
    ll ans=0,i,j,k,l,r,o;
    for(i=1;i*i*i<=n;i++)if(!p2[i])ans+=s2(n/i)-i;
    for(i=1;i*i*i*i<=n;i++)if(!p3[i])for(j=s3(i);j;j--)
    {
        k=gcd(j*j,i);
        l=j*j/k;
        r=s3(n/i)/l;
        if(!p2[k=i/k])for(o=0;o<a[k].size();o++)ans+=mu[a[k][o]]*(b[a[k][o]][r/a[k][o]]-b[a[k][o]][i/l/a[k][o]]);
    }
    return ans;
}
class SemiPerfectPower
{
    public:
        long long count(long long L, long long R)
        {
            for(i=1;i<M;i++)for(j=i;j<M;j+=i)a[j].pb(i);
            for(i=2;i*i<N;i++)
            {
                for(j=i*i;j<N;j+=i*i)p2[j]=1;
                for(j=i*i*i;j<N;j+=i*i*i)p3[j]=1;
            }
            for(mu[1]=1,i=2;i<M;i++)if(!p2[i])mu[i]=-mu[i/a[i][1]];
            for(i=1;i<M;i++)
            {
                b[i].pb(0);
                for(j=i,k=0;j<N;j+=i)b[i].pb(k+=!p2[j]);
            }
            return work(R)-work(L-1);
        }
};
