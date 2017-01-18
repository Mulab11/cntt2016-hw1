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
#define MAXN 5010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct ShoutterDiv1
{
	struct itv
	{
		int l;
		int r;
		friend bool operator <(itv x,itv y)
		{
			return x.l<y.l;
		}
	};
	string S1000,S100,S10,S1,T1000,T100,T10,T1;
	itv a[MAXN];
	int n;
	int ans;
	int tls[MAXN],tln,mx;
	map<int,int>h;
	int minr=INF;
	int count(	vector<string>s1000,vector<string>s100,vector<string>s10,vector<string>s1,
				vector<string>t1000,vector<string>t100,vector<string>t10,vector<string>t1)
				{
		int i;
		for(i=0;i<s1000.size();i++)
		{
			S1000+=s1000[i];
		}
		for(i=0;i<s100.size();i++)
		{
			S100+=s100[i];
		}
		for(i=0;i<s10.size();i++)
		{
			S10+=s10[i];
		}
		for(i=0;i<s1.size();i++)
		{
			S1+=s1[i];
		}
		for(i=0;i<t1000.size();i++)
		{
			T1000+=t1000[i];
		}
		for(i=0;i<t100.size();i++)
		{
			T100+=t100[i];
		}
		for(i=0;i<s10.size();i++)
		{
			T10+=t10[i];
		}
		for(i=0;i<s1.size();i++)
		{
			T1+=t1[i];
		}
		n=S1000.size();
		for(i=1;i<=n;i++)
		{
			a[i].l=(S1000[i-1]-'0')*1000+(S100[i-1]-'0')*100+(S10[i-1]-'0')*10+S1[i-1]-'0';
			a[i].r=(T1000[i-1]-'0')*1000+(T100[i-1]-'0')*100+(T10[i-1]-'0')*10+T1[i-1]-'0';
			tls[++tln]=a[i].l;
			tls[++tln]=a[i].r;
		}
		sort(tls+1,tls+tln+1);
		for(i=1;i<=tln;i++)
		{
			if(tls[i]!=tls[i-1]||i==1)
			{
				h[tls[i]]=++mx;
			}
		}
		for(i=1;i<=n;i++)
		{
			a[i].l=h[a[i].l];
			a[i].r=h[a[i].r];
			minr=min(minr,a[i].r);
		}
		sort(a+1,a+n+1);
		for(i=1;i<=n;i++)
		{
			int R=minr;
			int wzh=1;
			while(wzh<=n)
			{
				if(a[i].l<=R)
				{
					R=max(R,a[i].r);
				}
				int now=0;
				while(wzh<=n&&a[wzh].l<=R)
				{
					if(a[wzh].r>a[now].r)
					{
						now=wzh;
					}
					wzh++;
				}
				if(!now)
				{
					return -1;
				}
				if(wzh>n)
				{
					break;
				}
				ans++;
				R=max(R,a[now].r);
			}
		}
		return ans;
	}
};