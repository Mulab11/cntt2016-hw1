#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

struct node
{
	int data,next;
}e[1000000];

int a[40010],b[40010],head[40010],miu[40010],cur[40010],g[40010];
bool ok[40010];

int gcd(int x,int y)
{
	while (y)
	{
		ll r=x%y;x=y;y=r;
	}
	return x;
}

void push(int k,int x,int y)
{
	e[k].data=y;e[k].next=0;
	if (!head[x]) head[x]=k; else e[cur[x]].next=k;
	cur[x]=k;
}

ll sqr4(int x)
{
	return ll(x)*x*x*x;
}

ll calc(ll n)
{
	memset(head,0,sizeof(head));int ecnt=0;
	for (int i=1;sqr4(i)<=n;i++)
	{
		int t=i,p=1,x=1;
		for (int j=2;j*j<=t;j++)
			if (t%j==0)
			{
				if (t%(j*j)==0) p=0;
				while (t%j==0) t/=j;
				p=-p;x*=j;
			}
		if (t>1) {p=-p;x*=t;}
		miu[i]=p;
		for (int j=x;sqr4(j)<=n;j+=x)
			if (j*j%i==0) push(++ecnt,i,j);
	}
	ll ans=0;
	for (int i=1;ll(i)*i*i<=n;i++)
	{
		int t=i;bool ok=1;
		for (int j=2;j*j<=t;j++)
			if (t%j==0)
			{
				if (t%(j*j)==0) {ok=0;break;}
				t/=j;
			}
		if (!ok) continue;
		int l=1,r=300000000;
		while (l<=r)
		{
			int mid=(l+r)>>1;
			if (ll(mid)*mid<=n/i) l=mid+1; else r=mid-1;
		}
		ans=ans+r-i;
	}
	memset(g,0,sizeof(g));
	memset(ok,0,sizeof(ok));
	int x=1;
	for (int i=1;sqr4(i)<=n;i++)
	{
		int l=1,r=500000;
		while (l<=r)
		{
			ll mid=(l+r)>>1;
			if (ll(mid)*mid*mid<=n/i) l=mid+1; else r=mid-1;
		}
		if (i==x*x*x)
		{
			for (int j=1;sqr4(j*x)<=n;j++) g[j*x]+=miu[j];
			x++;
		}
		int t=i;bool ok2=1;
		for (int j=2;j*j<=t;j++)
			if (t%j==0)
			{
				if (t%(j*j*j)==0) {ok2=0;break;}
				t/=j;if (t%j==0) t/=j;
			}
		if (!ok2) continue;
		int m=0;
		for (int j=1;j*j<=i;j++)
			if (i%j==0)
			{
				a[++m]=j;
				if (j*j!=i) a[++m]=i/j;
			}
		sort(a+1,a+m+1);
		int cnt=0;
		for (int j=m;j;j--)
		{
			int p=head[a[j]];
			while (p)
			{
				int x=e[p].data;
				if (x*x/a[j]>r) break;
				if (!ok[x])
				{
					ok[x]=1;b[++cnt]=x;
					int t=x*x/a[j];
					ans=ans+(r/t-i/t)*g[x];
				}
				p=e[p].next;
			}
		}
		for (int i=1;i<=cnt;i++) ok[b[i]]=0;
	}
	return ans;
}

struct SemiPerfectPower 
{
    long long count(long long L, long long R)
    {
    	return calc(R)-calc(L-1);
    }
};
