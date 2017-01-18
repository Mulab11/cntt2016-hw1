#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<queue>
#include<stack>
using namespace std;
#define MAXN 1000010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
ll L,R;
ll mn[MAXN];
ll a[MAXN];
ll tmn[MAXN];
ll cnt[MAXN];
ll M;
ll ans;
void cal(ll p,ll c,ll m)
{
	ll i,j;
	ll rem=m;
	for(i=0;i<m;i++)
	{
		cnt[i]=0;
		a[i]=10000000000000ll;
	}
	for(i=0;i<p*c;i++)
	{//枚举k 
		for(j=0;j<m;j+=p)
		{
			ll t=(j+i*i)%m;
			if(cnt[t]<c)
			{
				int tmp=j;
				while(tmp%p==0)
				{
					cnt[t]++;
					tmp/=p;
					if(cnt[t]>=c)
					{
						rem--;
						a[t]=i*i+1;
						break;
					}
				}
			}
		}
	}
	ll MM=M*m;
	for(i=0;i<MM;i++)
	{
		tmn[i]=max(mn[i%M],a[i%m]);//合并 
	}
	for(i=0;i<MM;i++)
	{
		mn[i]=tmn[i];
	}
	M=MM;
}
struct SparseFactorial
{
	ll getCount(ll _L,ll _R,ll m)
	{
		ll i;
		L=_L-1;
		R=_R;
		M=1;
		for(i=2;i<=m;i++)
		{
			if(!(m%i))
			{
				ll c=0,mm=1;
				while(!(m%i))
				{
					m/=i;
					c++;
					mm*=i;
				}//分解质因数 
				cal(i,c,mm);
			}
		}
		for(i=0;i<M;i++)
		{
			ll lim=mn[i]/M*M+i;
			if(lim<mn[i])
			{
				lim+=M;
			}
			if(lim<=R)
			{
				ans+=(R-lim)/M+1;
			}
			if(lim<=L)
			{
				ans-=(L-lim)/M+1;//计算答案 
			}
		}
		return ans;
	}
};

/*

*/