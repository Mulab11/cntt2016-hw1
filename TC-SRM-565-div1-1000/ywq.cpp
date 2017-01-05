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

const int mod=1000000009;
const int inf=2000000000;

int n;
pii d1[55],d2[55],d3[55];

int solve0(pii *a,int m)
{
	int ans=1,i=0;
	while (i<m)
	{
		int j=i;
		while (j<m&&a[i].x==a[j].x) j++;
		if (a[i].y) return 0;
		int k=i;
		for (int p=i+1;p<j;p++)
		{
			while (a[k].y<a[p].y) k++;
			ans=ll(ans)*(k-i)%mod;
		}
		i=j;
	}
	return ans;
}

int solve1(vi a,vi b,vi c,int k)
{
	int m1=1,m2=1,m3=1;
	d1[0]=mp(0,0);d2[0]=mp(0,0);d3[0]=mp(0,0);
	for (int i=0;i<n;i++)
		if (b[i]-c[i]==b[k]-c[k]&&b[i]>=b[k]&&c[i]>=c[k])
		{
			if (b[i]-a[i]>a[k]+b[k]) return 0;
			if (b[i]-a[i]==a[k]+b[k])
				d1[m1++]=mp(0,a[i]);
			else
			{
				int t=a[i]+b[i]-a[k]-b[k];
				if (t<0||(t&1)) return 0; else t>>=1;
				d1[m1++]=mp(a[i]-t,t);
			}
		}
		else
			if (c[i]-a[i]==c[k]-a[k]&&c[i]>=c[k]&&a[i]>=a[k])
			{
				if (c[i]-b[i]>b[k]+c[k]) return 0;
				if (c[i]-b[i]==b[k]+c[k])
					d2[m2++]=mp(0,b[i]);
				else
				{
					int t=b[i]+c[i]-b[k]-c[k];
					if (t<0||(t&1)) return 0; else t>>=1;
					d2[m2++]=mp(b[i]-t,t);
				}
			}
			else
				if (a[i]-b[i]==a[k]-b[k]&&a[i]>=a[k]&&b[i]>=b[k])
				{
					if (a[i]-c[i]>c[k]+a[k]) return 0;
					if (a[i]-c[i]==c[k]+a[k])
						d3[m3++]=mp(0,c[i]);
					else
					{
						int t=c[i]+a[i]-c[k]-a[k];
						if (t<0||(t&1)) return 0; else t>>=1;
						d3[m3++]=mp(c[i]-t,t);
					}
				}
				else
					return 0;
	sort(d1,d1+m1);sort(d2,d2+m2);sort(d3,d3+m3);
	return ll(solve0(d1,m1))*solve0(d2,m2)%mod*solve0(d3,m3)%mod;
}

int solve3(vi a,vi b,vi c,int w1,int w2)
{
	int m1=2,m2=1;
	d1[0]=mp(0,0);d1[1]=mp(w1,0);d2[0]=mp(0,0);
	for (int i=0;i<n;i++)
		if (b[i]-c[i]==w2)
		{
			if (c[i]-a[i]>w1) return 0;
			if (c[i]-a[i]==w1)
				d1[m1++]=mp(0,a[i]);
			else
			{
				int t=a[i]+c[i]-w1;
				if (t<0||(t&1)) return 0; else t>>=1;
				d1[m1++]=mp(a[i]-t,t);
			}
		}
		else
			if (a[i]-c[i]==w1)
			{
				if (c[i]-b[i]>w2) return 0;
				if (c[i]-b[i]==w2)
					d2[m2++]=mp(0,b[i]);
				else
				{
					int t=b[i]+c[i]-w2;
					if (t<0||(t&1)) return 0; else t>>=1;
					d2[m2++]=mp(b[i]-t,t);
				}
			}
			else
				return 0;
	sort(d1,d1+m1);sort(d2,d2+m2);
	return ll(solve0(d1,m1))*solve0(d2,m2)%mod;
}

int solve2(vi a,vi b,vi c)
{
	int ans=0;
	if (a[0]>c[0]&&b[0]>c[0]) ans=(ans+solve3(a,b,c,a[0]-c[0],b[0]-c[0]))%mod;
	if (b[0]>c[0])
	{
		int mi=inf;
		for (int i=0;i<n;i++) mi=min(mi,a[i]+c[i]);
		if (abs(a[0]-c[0])!=mi) ans=(ans+solve3(a,b,c,mi,b[0]-c[0]))%mod;
		if (c[0]>a[0]) ans=(ans+solve3(a,b,c,c[0]-a[0],b[0]-c[0]))%mod;
	}
	if (a[0]>c[0])
	{
		int mi=inf;
		for (int i=0;i<n;i++) mi=min(mi,b[i]+c[i]);
		if (abs(b[0]-c[0])!=mi) ans=(ans+solve3(a,b,c,a[0]-c[0],mi))%mod;
		if (c[0]>b[0]) ans=(ans+solve3(a,b,c,a[0]-c[0],c[0]-b[0]))%mod;
	}
	return ans;
}

struct UnknownTree 
{
    int getCount(vector <int> distancesA, vector <int> distancesB, vector <int> distancesC)
    {
    	n=distancesA.size();
    	int ans=0;
    	for (int i=0;i<n;i++) ans=(ans+solve1(distancesA,distancesB,distancesC,i))%mod; //three points dont't lie on a path and the intersection is i
    	ans=(ans+solve2(distancesA,distancesB,distancesC))%mod;
    	ans=(ans+solve2(distancesC,distancesA,distancesB))%mod;
    	ans=(ans+solve2(distancesB,distancesC,distancesA))%mod;
    	return ans;
    }
};
