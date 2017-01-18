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
#define MAXN 11
#define MAXM 60
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
int n;
struct data
{
	int v[MAXM];
	data()
	{
		memset(v,0,sizeof(v));
	}
	friend bool operator <(data x,data y)
	{
		int i;
		for(i=1;i<=n;i++)
		{
			if(x.v[i]!=y.v[i])
			{
				return x.v[i]<y.v[i];
			}
		}
		return 0;
	}
};
int d;
int lim1,lim2;
int dv;
char now[MAXN];
map<data,int>h;
char gs[MAXM][MAXN];
int as[MAXM];
struct EllysBulls
{
	string getNumber(vector<string>_gs,vector<int>_as)
	{
		int i,j,k;
		n=_gs.size();
		d=_gs[0].size();
		dv=d/2;
		//<<d<<'!'<<dv<<endl;
		lim1=int(pow(10.0,1.0*dv));
		lim2=int(pow(10.0,1.0*(d-dv)));
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=d;j++)
			{
				gs[i][j]=_gs[i-1][j-1];
			}
			as[i]=_as[i-1];
		}
		for(i=0;i<lim1;i++)
		{
			int t=i;
			for(j=dv;j;j--)
			{
				now[j]=t%10+'0';
				t/=10;
			}
			
			//<<i<<endl;
			for(j=1;j<=dv;j++)
			{
				//<<now[j];
			}
			//<<'@'<<endl;
			data ths;
			for(j=1;j<=n;j++)
			{
				ths.v[j]=as[j];
				for(k=1;k<=dv;k++)
				{
					ths.v[j]-=(gs[j][k]==now[k]);
				}
				//<<ths.v[j]<<' ';
			}
			//<<endl;
			if(h.find(ths)==h.end())
			{
				h[ths]=i;
			}
			else
			{
				h[ths]=-1;
			}
		}
		bool flag=0;
		int ans1,ans2;
		for(i=0;i<lim2;i++)
		{
			int t=i;
			for(j=d;j>dv;j--)
			{
				now[j]=t%10+'0';
				t/=10;
			}
			data ths;
			for(j=1;j<=n;j++)
			{
				for(k=dv+1;k<=d;k++)
				{
					ths.v[j]+=(gs[j][k]==now[k]);
				}
			}
			if(h.find(ths)!=h.end())
			{
				if(h[ths]==-1||flag)
				{
					return "Ambiguity";
				}
				ans1=h[ths];
				ans2=i;
				flag=1;
			}
		}
		if(flag)
		{
			//<<ans1<<"!"<<ans2<<endl;
			for(i=d;i>dv;i--)
			{
				now[i]=ans2%10+'0';
				ans2/=10;
			}
			for(i=dv;i;i--)
			{
				now[i]=ans1%10+'0';
				ans1/=10;
			}
			string re="";
			for(i=1;i<=d;i++)
			{
				re+=now[i];
			}
			return re;
		}
		else
		{
			return "Liar";
		}
	}
};