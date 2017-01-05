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

const int M=1000000009;
const int a[9][2]={{2,1},{3,1},{2,2},{5,1},{3,1},{7,1},{2,3},{3,2},{5,1}};

int mod,n,k,b[50];

int power(int x,int y)
{
	int t=1;
	while (y)
	{
		if (y&1) t=ll(t)*x%mod;
		y>>=1;x=ll(x)*x%mod;
	}
	return t;
}

struct matrix
{
	int d[20][20];
}c,f[50],g[50],ans;

matrix operator *(matrix a,matrix b)
{
	for (int i=0;i<=k;i++)
		for (int j=0;j<=k;j++)
		{
			c.d[i][j]=0;
			for (int p=0;p<=k;p++) c.d[i][j]=(ll(a.d[i][p])*b.d[p][j]+c.d[i][j])%mod;
		}
	return c;
}

int solve(int N,int K,int B)
{
	n=N;k=K;
	int l=0;
	while (N)
	{
		b[++l]=N%B;N/=B;
	}
	for (int i=0;i<=k;i++)
		for (int j=0;j<=k;j++)
			f[0].d[i][j]=g[0].d[i][j]=(i==j);
	for (int i=1;i<=l;i++)
	{
		g[i]=g[i-1];
		for (int j=1;j<B;j++) g[i]=f[i-1]*g[i];
		for (int j=0;j<=k;j++)
			for (int p=0;p<=k;p++)
				f[i].d[j][p]=0;
		for (int j=0;j<k;j++)
			for (int p=j;p<k;p++)
				f[i].d[j][p]=1;
		for (int j=0;j<k;j++) f[i].d[k][j]=i-1;
		f[i].d[k][k]=1;
		f[i]=g[i]*f[i];
	}
	ans=f[0];
	for (int i=l;i;i--)
		for (int j=0;j<b[i];j++)
			ans=ans*f[i];
	return ans.d[k][k-1]%mod;
}

struct MegaFactorial 
{
    int countTrailingZeros(int N, int K, int B)
    {
    	mod=M;int ans=solve(N,K,a[B-2][0]);
    	mod=a[B-2][1];ans-=solve(N,K,a[B-2][0]);
    	mod=M;ans=ll(ans)*power(a[B-2][1],mod-2)%mod;
    	return (ans+mod)%mod;
    }
};
