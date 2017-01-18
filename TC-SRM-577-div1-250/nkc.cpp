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
struct EllysRoomAssignmentsDiv1
{
	struct ps
	{
		int a;
		int I;
		friend bool operator <(ps x,ps y)
		{
			return x.a>y.a;	
		}
	};
	string s;
	int n;
	ps a[MAXN];
	double getAverage(vector<string> g)
	{
		int i,j;
		for(i=0;i<g.size();i++)
		{
			s+=g[i];
		}
		s+=" ";
		int now=0;
		for(i=0;i<s.size();i++)
		{
			if(s[i]==' ')
			{
				a[++n].a=now;
				a[n].I=n;
				now=0;
			}
			else
			{
				now*=10;
				now+=s[i]-'0';
			}
		}
		int S=ceil(1.0*n/20);
		double re=0;
		re=a[1].a;
		sort(a+1,a+n+1);
		int T=0;
		for(i=1;i<=n;i++)
		{
			bool flag=0;
			double t=0;
			for(j=i;j<=n&&j<i+S;j++)
			{
				t+=a[j].a;
				if(a[j].I==1)
				{
					flag=1;
				}
			}
			
			if(!flag)
			{
				if(j-i!=S)
				{
					return (re+(t/(j-i)))/(T+1)*(j-i)/S+(re/T)*(S-(j-i))/S;
				}
				re+=t/S;
			}
			T++;
			i=j-1;
		}
		return re/T;
	}
};