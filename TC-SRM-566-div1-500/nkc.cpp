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
#define MAXN 360
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
int n;
struct PenguinEmperor
{
	struct mat
	{
		int x[MAXN];
		mat()
		{
			memset(x,0,sizeof(x));
		}
		friend mat operator *(mat x,mat y)
		{
			int i,j;
			mat z;
			for(i=0;i<n;i++)
			{
				for(j=0;j<n;j++)
				{
					(z.x[i]+=(ll)x.x[(i-j+n)%n]*y.x[j]%MOD)%=MOD;
				}
			}
			return z;
		}
	};
	mat b;
	mat A,B;
	mat bb;
	ll countJourneys(int _n,ll y)
	{
		int i;
		n=_n;
		A.x[0]=B.x[0]=1;
		bb.x[0]=1;
		for(i=1;i<=n;i++)
		{
			b=mat();
			b.x[i]=b.x[n-i]=1;
			B=B*b;
			if(i==y%n)
			{
				bb=B;
			}
		}
		ll Y=y/n;
		while(Y)
		{
			if(Y&1)
			{
				A=A*B;
			}
			B=B*B;
			Y>>=1;
		}
		A=A*bb;
		return A.x[0];
	}
};