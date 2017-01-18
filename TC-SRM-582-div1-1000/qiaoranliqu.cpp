#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55005
#define M 2000005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
bool vis[M];
int prime[M/10],mu[M];
vector<int>v[N],zi[N];
long long root(long long x,int y)
{
		long long l=0,r,mid=0,i;
		if (y==1) return x;
		if (y==2) r=(long long)3e9;
		if (y==3) r=(long long)(2e6)+5;
		if (y==4) r=53200;
		while ((l+r)>>1!=mid)
		{
				mid=(l+r)>>1;
				long long now=1;
				for (i=1;i<=y;++i) now*=mid;
				if (now<=x) l=mid; else r=mid;
		}
		return l;
}

long long gcd(long long x,long long y)
{
		return !y?x:gcd(y,x%y);
}

void pre()
{
		long long lim=root((long long)8e18,4);
		mu[1]=1;
		for (i=2;i<M;++i)
		{
				if (!vis[i])
				{
						prime[++prime[0]]=i;
						mu[i]=-1;
				}
				for (j=1;i*prime[j]<M;++j)
				{
						vis[i*prime[j]]=1;
						if (i%prime[j]==0)
						{
							mu[i*prime[j]]=0;
							break;
						}
						mu[i*prime[j]]=-mu[i];
				}
		}
		for (i=1;i<N;++i)
		{
				for (j=1;j*j<=i;++j)
					if (i%j==0)
					{
						if (mu[j]) zi[i].pb(j);
						if (j*j!=i&&mu[i/j]) zi[i].pb(i/j);
					}
		}
		for (i=1;i<=lim;++i)
		{
				v[i].pb(0);
				long long bao=root(((long long)(8e18))/i,3),now=1;
				for (j=i;j<=bao;j+=i) 
				{
						v[i].pb(0);
						v[i][now]+=v[i][now-1];
						if (mu[j]) v[i][now]++;
						++now;
				}
		}
}

int good(long long x)
{
		long long i;
		for (i=2;i*i<=x;++i)
		{
				int cnt=0;
				while (x%i==0) ++cnt,x/=i;
				if (cnt>=3) return 0;
		}
		return 1;
}

long long Count3(long long x)
{
		long long lim=root(x,4),i,j,k,sum=0;
		for (i=1;i<=lim;++i)
			if (good(i))
			{
					for (j=1;j*j*j<=i;++j)
					{
							long long kk=1ll*j*j/gcd(1ll*j*j,i),bb=i/gcd(1ll*j*j,i),str=i/kk,End=root(x/i,3)/kk;
							if (!mu[bb]) continue;
							for (k=0;k<(int)zi[bb].size();++k)
							{
									long long fu=zi[bb][k];
									sum+=mu[fu]*(v[fu][(int)(End/fu)]-v[fu][(int)(str/fu)]);
							}
					}
			}
		return sum;
}

long long Count2(long long x)
{
	long long lim=root(x,3),i,sum=0;
	for (i=1;i<=lim;++i) if (mu[i])	sum+=root(x/i,2)-i;
	return sum;
}

class SemiPerfectPower{
	public:
	long long count(long long L, long long R)
	{
			pre();
			return Count3(R)-Count3(L-1)+Count2(R)-Count2(L-1);
	}
}MRT;
