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
int N;
int n;
int sc[3];
struct mat
{
	int x[210][210];
	mat()
	{
		memset(x,0,sizeof(x));
	}
	friend mat operator *(mat x,mat y)
	{
		int i,j,k;
		mat z;
		for(i=0;i<=N;i++)
		{
			for(j=0;j<=N;j++)
			{
				for(k=0;k<=N;k++)
				{
					(z.x[i][j]+=(ll)x.x[i][k]*y.x[k][j]%MOD)%=MOD;
				}
			}
		}
		return z;
	}
};
mat a,b,c;
int pt(int i,int j)
{
	return i*(n+1)+j;
}
struct ConversionMachine
{
	int countAll(string _s,string _t,vector<int>_c,int mx)
	{
		int i,j,k;
		n=_s.size();
		int y=0;
		for(i=0;i<n;i++)
		{
			int s=_s[i]-'a';
			int t=_t[i]-'a';
			int d=0;
			while(s!=t)
			{
				mx-=_c[s];
				if(mx<0)
				{
					return 0;
				}
				s=(s+1)%3;
				d++;
				y++;
			}
			sc[d]++;
		}
		int C=_c[0]+_c[1]+_c[2];
		y+=mx/C*3;
		N=(n+1)*(n+1)+1;
		for(i=0;i<=N;i++)
		{
			a.x[i][i]=1;
		}
		c.x[0][pt(sc[0],sc[1])]=1;
		c.x[0][N]=c.x[0][pt(n,0)];
		for(i=0;i<=n;i++)
		{
			for(j=0;i+j<=n;j++)
			{
				k=n-i-j;
				if(i!=n&&k!=0)
				{
					b.x[pt(i+1,j)][pt(i,j)]=i+1;
				}
				if(j!=n&&i!=0)
				{
					b.x[pt(i-1,j+1)][pt(i,j)]=j+1;
				}
				if(k!=n&&j!=0)
				{
					b.x[pt(i,j-1)][pt(i,j)]=k+1;
				}
			}
		}
		b.x[N][N]=1;
		b.x[pt(n-1,1)][N]=1;
		while(y)
		{
			if(y&1)
			{
				a=a*b;
			}
			b=b*b;
			y>>=1;
		}
		c=c*a;
		return c.x[0][N];
	}
};

/*

*/