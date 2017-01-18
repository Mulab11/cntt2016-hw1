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
#define MAXN 10010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
string rx,bx,by;
int n,m;
int x[MAXN],y[MAXN];
int X[MAXN];
ll s1[MAXN],s2[MAXN],ss1[MAXN],ss2[MAXN];
int lim=10005;
bool hp[MAXN];
struct Ear
{
	ll getCount(vector<string>_rx,vector<string>_bx,vector<string>_by)
	{
		int i,j;
		for(i=0;i<_rx.size();i++)
		{//蛋疼菊紧的读入 
			rx+=_rx[i];
		}
		for(i=0;i<_bx.size();i++)
		{
			bx+=_bx[i];
		}
		for(i=0;i<_by.size();i++)
		{
			by+=_by[i];
		}
		rx+=" ";
		bx+=" ";
		by+=" ";
		int tmp=0;
		for(i=0;i<rx.size();i++)
		{
			if(rx[i]==' ')
			{
				X[++n]=tmp;
				tmp=0;
			}
			else
			{
				tmp*=10;
				tmp+=rx[i]-'0';
			}
		}
		for(i=0;i<bx.size();i++)
		{
			if(bx[i]==' ')
			{
				y[++m]=tmp;
				tmp=0;
			}
			else
			{
				tmp*=10;
				tmp+=bx[i]-'0';
			}
		}
		m=0;
		for(i=0;i<by.size();i++)
		{
			if(by[i]==' ')
			{
				x[++m]=tmp;
				tmp=0;
			}
			else
			{
				tmp*=10;
				tmp+=by[i]-'0';
			}
		}
		for(i=1;i<=n;i++)
		{
			hp[X[i]]=1;
		}
		for(i=1;i<=lim;i++)
		{//预处理前缀和 
			s1[i]=s1[i-1]+hp[i];
			ss1[i]=ss1[i-1]+hp[i]*s1[i-1];
		}
		for(i=lim-1;i;i--)
		{
			s2[i]=s2[i+1]+hp[i];
			ss2[i]=ss2[i+1]+hp[i]*s2[i+1];
		}
		ll ans=0;
		for(i=1;i<=m;i++)
		{
			for(j=1;j<=m;j++)
			{//枚举两个蓝点 
				if(x[j]<x[i])
				{
					ll liml=y[i],limr=y[i];
					if(y[j]<y[i])
					{
						liml=y[i]-(ll)(y[i]-y[j])*x[i]/(x[i]-x[j]);
					}
					else
					{
						limr=y[i]+(ll)(y[j]-y[i])*x[i]/(x[i]-x[j]);
					}
					ll t1=0,t2=0;
					if(liml>1)
					{//计算贡献 
						t1+=ss2[1]-ss2[liml];
						t1-=s2[y[j]]*(s2[1]-s2[liml]);
					}
					if(limr<lim)
					{
						t2+=ss1[lim]-ss1[limr];
						t2-=s1[y[j]]*(s1[lim]-s1[limr]);
					}
					ans+=t1*t2;
				}
			}
		}
		return ans;
	}
};