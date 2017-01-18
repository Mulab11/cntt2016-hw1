#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<queue>
#include<map>
#include<bitset>
#include<stack>
#include<vector>
#include<set>
using namespace std;
#define MAXN 1010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define ll long long
#define eps 1e-8
int nc,pc;
bool has[MAXN];
int to[MAXN];
int tot;
int l[MAXN],r[MAXN];
int s[MAXN];
int ans=INF;
bool itr[MAXN];
int mx[MAXN],mn[MAXN];
int cal()
{
	int i;
	for(i=0;i<200;i++)
	{
		mx[i]=-INF;
		mn[i]=INF;
		itr[i]=0;
	}
	for(i=1;i<=tot;i++)
	{
		itr[r[i]]=1;
		mn[r[i]]=min(mn[r[i]],l[i]);
		mx[r[i]]=max(mx[r[i]],l[i]);
	}
	int re=0;
	for(i=0;i<200;i++)
	{
		if(itr[i])
		{
			if(mn[i]<i)
			{
				re+=nc*(i-mn[i]);
			}
			if(mx[i]>i)
			{
				re+=pc*(mx[i]-i);
			}
		}
	}
	return re;
}
bool jud(int x)
{
	int i;
	for(i=1;i<x;i++)
	{
		if((l[i]<l[x]&&r[i]>r[x])||(l[i]>l[x]&&r[i]<r[x]))
		{
			return 0;
		}
	}
	return 1;
}
struct NextAndPrev
{
	int getMinimum(int _nc,int _pc,string _s,string _t)
	{
		int i,j;
		nc=_nc;
		pc=_pc;
		for(i=0;i<_s.size();i++)
		{
			if(has[_s[i]-'a']&&to[_s[i]-'a']!=_t[i]-'a')
			{
				return -1;
			}
			has[_s[i]-'a']=1;
			itr[_t[i]-'a']=1;
			to[_s[i]-'a']=_t[i]-'a';
		}
		bool flag=0;
		for(i=0;i<26;i++)
		{
			if(!itr[i])
			{
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			if(_s==_t)
			{
				return 0;
			}
			return -1;
		}
		tot=flag=0;
		for(i=0;i<26;i++)
		{
			if(has[i])
			{
				l[++tot]=i;
				r[tot]=to[i];
				if(!jud(tot))
				{
					flag=1;
					break;
				}
			}
		}
		if(!flag)
		{
			ans=min(ans,cal());
		}
		for(i=0;i<26;i++)
		{
			tot=flag=0;
			for(j=0;j<26;j++)
			{
				if(has[j])
				{
					if(j<=i)
					{
						l[++tot]=j+26+100;
						r[tot]=to[j]+100;
					}
					else
					{
						l[++tot]=j+100;
						r[tot]=to[j]+100;
					}
					if(!jud(tot))
					{
						flag=1;
						break;
					}
				}
			}
			if(!flag)
			{
				ans=min(ans,cal());
			}
			tot=flag=0;
			for(j=0;j<26;j++)
			{
				if(has[j])
				{
					if(j<=i)
					{
						l[++tot]=j+100;
						r[tot]=to[j]+100;
					}
					else
					{
						l[++tot]=j-26+100;
						r[tot]=to[j]+100;
					}
					if(!jud(tot))
					{
						flag=1;
						break;
					}
				}
			}
			if(!flag)
			{
				ans=min(ans,cal());
			}
			tot=flag=0;
			for(j=0;j<26;j++)
			{
				if(has[j])
				{
					if(j<=i)
					{
						l[++tot]=j+52+100;
						r[tot]=to[j]+100;
					}
					else
					{
						l[++tot]=j+26+100;
						r[tot]=to[j]+100;
					}
					if(!jud(tot))
					{
						flag=1;
						break;
					}
				}
			}
			if(!flag)
			{
				ans=min(ans,cal());
			}
			tot=flag=0;
			for(j=0;j<26;j++)
			{
				if(has[j])
				{
					if(j<=i)
					{
						l[++tot]=j-26+100;
						r[tot]=to[j]+100;
					}
					else
					{
						l[++tot]=j-52+100;
						r[tot]=to[j]+100;
					}
					if(!jud(tot))
					{
						flag=1;
						break;
					}
				}
			}
			if(!flag)
			{
				ans=min(ans,cal());
			}
		}
		return ans==INF?-1:ans;
	}
};

/*
55
654
jgjhgjggjhhghghhggjjgjjhhjgjjghgggjhgj
rzrqzrzzrqqzqzqqzzrrzrrqqrzrrzqzzzrqzr
*/