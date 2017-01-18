#include<iostream>
#include<cstdio>
#define ll long long
#define mod 1000000007
#define N 1000010
using namespace std;
int mi[N],q[N*2],ni[N*2],nq[N*2];
ll C(ll n,ll m)
{
	if(n<m) return 0;
	return (ll)q[n]*nq[m]%mod*nq[n-m]%mod;
}
ll sol(ll x,ll y,ll k)
{
	if(k<=0) return 0;
	ll sum=0;
	for(ll i=0;i<=k;i++)
	{
		if((k-i)%2!=(x+y)%2) continue;
		ll p=x,q=y;
		p-=i;
		q-=i;
		ll a=(k-i+x-y)/2,b=k-i-a;
		if(a<0||b<0) continue;
		p-=a;
		q-=b;
		if(p<0||q<0) continue;
		(sum+=C(p+k-1,k-1)*C(k,i)%mod*mi[i]%mod*C(k-i,a))%=mod;
	}
	return sum;
}
struct LittleElephantAndBoard
{
int getNumber(int m,int a,int b,int c)
{
	a=m-a;
	b=m-b;
	c=m-c;
	if(a<0||b<0||c<0) return 0;
	mi[0]=q[0]=ni[1]=nq[0]=1;
	for(ll i=1;i<=m;i++) mi[i]=mi[i-1]*2%mod;
	for(ll i=1;i<=m*2;i++) q[i]=(ll)q[i-1]*i%mod;
	for(ll i=2;i<=m*2;i++) ni[i]=(ll)(mod-mod/i)*ni[mod%i]%mod;
	for(ll i=1;i<=m*2;i++) nq[i]=(ll)nq[i-1]*ni[i]%mod;
	return int((sol(b,c,a-1)+sol(b,c,a)*2+sol(b,c,a+1))*2%mod);
}
};