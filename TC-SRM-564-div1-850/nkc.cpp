#include<iostream>
#include<cstdio>
#include<vector>
#define N 70000
#define mod 1000000007
#define ll long long
using namespace std;
ll n,m,a[N],d[N],f[N][2],ans;
void get(ll k)
{
	f[0][0]=1;
	for(ll i=1;i<=n;i++)
	{
		if(a[i]&k)
		{
			ll o=1,s=0;
			for(ll j=n;j>i;j--)
			{
				if(a[j]&k) s++;
				o=o*(a[j]%k+1)%mod;
			}
			if(s%2==0^m/k%2==0) o=o*f[i-1][1]%mod;
			else o=o*f[i-1][0]%mod;
			(ans+=o)%=mod;
			f[i][0]=(f[i-1][0]*k+f[i-1][1]*(a[i]%k+1))%mod;
			f[i][1]=(f[i-1][1]*k+f[i-1][0]*(a[i]%k+1))%mod;
		}
		else
		{
			f[i][0]=f[i-1][0]*(a[i]%k+1)%mod;
			f[i][1]=f[i-1][1]*(a[i]%k+1)%mod;
		}
	}
}
struct DefectiveAddition
{
int count(vector<int> w,int M)
{
	d[0]=1;
	for(ll i=1;i<=30;i++) d[i]=d[i-1]*2;
	n=w.size();
	m=M;
	for(ll i=1;i<=n;i++) a[i]=w[i-1];
	for(ll i=30;i>=0;i--)
	{
		get(d[i]);
		ll s=0;
		for(ll j=1;j<=n;j++) if(a[j]&d[i]) s++;
		if(s%2==0^m/d[i]%2==0) break;
	}
	ll o=0;
	for(ll i=1;i<=n;i++) o^=a[i];
	if(o==m) ans++;
	return ans;
}
}r;