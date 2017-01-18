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
#define MAXN 50
#define MAXM 1000010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
int v[MAXN];
int a[MAXN][MAXN];
int mx;
int n,m;
int n1,n2;
vector<int>s1[MAXN],s2[MAXN];
int cs[MAXN];
int c[MAXN][MAXN];
int f[MAXN];
void m_i_m()
{//meet in the middle 
	int i,j;
	n1=n/2;
	n2=n-n1;
	int N1=(1<<n1);
	for(i=0;i<N1;i++)
	{
		int t=0,tv=0;
		for(j=1;j<=n1;j++)
		{
			if(i&(1<<(j-1)))
			{
				t++;
				tv+=v[j];
			}
		}
		s1[t].push_back(tv);
	}
	int N2=(1<<n2);
	for(i=0;i<N2;i++)
	{
		int t=0,tv=0;
		for(j=1;j<=n2;j++)
		{
			if(i&(1<<(j-1)))
			{
				t++;
				tv+=v[n1+j];
			}
		}
		s2[t].push_back(tv);
	}
	for(i=0;i<=n1;i++)
	{
		sort(s1[i].begin(),s1[i].end());
	}
	for(i=0;i<=n2;i++)
	{
		sort(s2[i].begin(),s2[i].end());
	}
	for(i=0;i<=n1;i++)
	{
		for(j=0;j<=n2;j++)
		{
			int p,q=s2[j].size()-1;
			for(p=0;p<s1[i].size();p++)
			{
				while(q>=0&&s1[i][p]+s2[j][q]>mx)
				{
					q--;
				}
				(cs[i+j]+=q+1)%=MOD;
			}
		}
	}
}
int gs()
{//求行列式 
	int i,j,k;
	int re=1;
	for(i=1;i<m;i++)
	{
		for(j=1;j<m;j++)
		{
			(a[i][j]+=MOD)%=MOD;
		}
	}
	for(i=1;i<m;i++)
	{
		for(j=i+1;j<m;j++)
		{
			while(a[j][i])
			{
				re=MOD-re;
				int b=a[i][i]/a[j][i];
				for(k=1;k<m;k++)
				{
					swap(a[j][k],a[i][k]);
					(a[j][k]+=MOD-(ll)a[i][k]*b%MOD)%=MOD;
				}
			}
		}
		re=(ll)re*a[i][i]%MOD;
	}
	return re;
}
void bde(int i,int j)
{
	a[i][i]++;
	a[j][j]++;
	a[i][j]--;
	a[j][i]--;
}
int cal(int x)
{//建图 
	int i,j;
	memset(a,0,sizeof(a));
	for(i=1;i<=x;i++)
	{
		for(j=1;j<i;j++)
		{
			if(i!=j)
			{
				bde(i,j);
			}
		}
		for(j=n+1;j<=m;j++)
		{
			bde(i,j);
		}
	}
	for(i=x+1;i<=n;i++)
	{
		for(j=n+1;j<=m;j++)
		{
			bde(i,j);
		}
	}
	for(i=n+1;i<=m;i++)
	{
		for(j=n+1;j<i;j++)
		{
			bde(i,j);
		}
	}
	return gs();
}
struct SweetFruits
{
	int countTrees(vector<int> _a,int _mx)
	{
		int i,j;
		m=_a.size();
		for(i=1;i<=m;i++)
		{
			if(_a[i-1]!=-1)
			{
				v[++n]=_a[i-1];
			}
		}
		mx=_mx;
		m_i_m();
		c[0][0]=1;
		for(i=1;i<=m;i++)
		{
			c[i][0]=1;
			for(j=1;j<=i;j++)
			{
				c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
			}
		}
		int re=0;
		for(i=0;i<=n;i++)
		{
			f[i]=cal(i);
			for(j=0;j<i;j++)
			{
				(f[i]+=MOD-(ll)f[j]*c[i][j]%MOD)%=MOD;//容斥原理 
			}
			(re+=(ll)f[i]*cs[i]%MOD)%=MOD;
		}
		return re;
	}
};

/*

*/