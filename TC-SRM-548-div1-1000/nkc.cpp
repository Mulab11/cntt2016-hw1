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
#define MAXN 60
#define MAXM 10010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
ll fac[MAXM],ine[MAXM];
ll f[MAXN][MAXN];
ll C(int n,int m)
{
	if(m>n)
	{
		return 0;
	}
	return fac[n]*ine[m]%MOD*ine[n-m]%MOD;
}
int n,m,k;
struct KingdomAndCities
{
	int howMany(int _n,int _k,int _m)
	{
		int i,j,I,J;
		n=_n;
		m=_m;
		k=_k;
		fac[0]=ine[0]=ine[1]=1;
		for(i=1;i<MAXM;i++)
		{
			fac[i]=fac[i-1]*i%MOD;
		}
		for(i=2;i<MAXM;i++)
		{
			ine[i]=(MOD-MOD/i)*ine[MOD%i]%MOD;
		}
		for(i=2;i<MAXM;i++)
		{
			(ine[i]*=ine[i-1])%=MOD;
		}
		f[1][0]=1;
		for(i=2;i<=n;i++)
		{
			for(j=0;j<=m;j++)
			{
				f[i][j]=C(i*(i-1)/2,j);
				for(I=1;I<i;I++)
				{
					for(J=0;J<=j;J++)
					{
						(f[i][j]+=MOD-C((i-I)*(i-I-1)/2,j-J)*C(i-1,I-1)%MOD*f[I][J]%MOD)%=MOD;
					}
				}
			}
		}
		if(k==0)
		{
			return f[n][m];
		}
		if(k==1)
		{
			ll re1=0;
			re1=C(n-1,2)*f[n-1][m-2]%MOD;
			ll re2=0;
			for(i=1;i<n-1;i++)
			{
				for(j=0;j<=m-2;j++)
				{
					(re2+=i*(n-1-i)%MOD*f[i][j]%MOD*f[n-1-i][m-2-j]%MOD*C(n-1,i))%=MOD;
				}
			}
			(re2*=500000004)%=MOD;
			return (re1+re2)%MOD;
		}
		if(k==2)
		{
			ll re1=0;
			re1=(C(n-2,2)*C(n-2,2)%MOD*f[n-2][m-4]%MOD+(n-2)*(n-2)%MOD*f[n-2][m-3]%MOD%MOD)%MOD;
			ll re2=0;
			ll re22=0;
			for(i=1;i<n-2;i++)
			{
				for(j=0;j<=m-3;j++)
				{
					(re2+=i*(n-2-i)%MOD*f[i][j]%MOD*f[n-2-i][m-3-j]%MOD*C(n-2,i))%=MOD;
					(re2+=i*(n-2-i)%MOD*(C(i,2)+C(n-2-i,2))%MOD*C(n-2,i)%MOD*f[i][j]%MOD*f[n-2-i][m-4-j]%MOD)%=MOD;
					(re22+=i*(n-2-i)%MOD*i%MOD*(n-2-i)%MOD*C(n-2,i)%MOD*f[i][j]%MOD*f[n-2-i][m-4-j]%MOD)%=MOD;
				}
			}
			(re22*=500000004)%=MOD;
			(re2+=re22)%=MOD;
			ll re3=0;
			for(i=1;i<n-2;i++)
			{
				for(I=1;i+I<n-2;I++)
				{
					for(j=0;j<=m-4;j++)
					{
						for(J=0;j+J<=m-3;J++)
						{
							(re3+=i*I%MOD*(n-2-i-I)%MOD*(n-2-i-I)%MOD
							*f[i][j]%MOD*f[I][J]%MOD*f[n-2-i-I][m-4-j-J]%MOD
							*C(n-2,i)%MOD*C(n-2-i,I)%MOD
							)%=MOD;
						}
					}
				}
			}
			return (re1+re2+re3)%MOD;
		}
	}
};