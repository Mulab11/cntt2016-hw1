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
#define MAXN 1610
#define MAXM 1010
#define INF 1000000000
#define MOD 555555555
#define eps 1e-8
#define ll long long
struct XorBoard
{
	int C[MAXN][MAXN];
	int f[MAXN][MAXN];
	int S[MAXN][MAXN];
	ll ans;
	int count(int n,int m,int cn,int cm,int s)
	{
		int i,j;
		C[0][0]=1;
		for(i=1;i<MAXN;i++)
		{
			C[i][0]=1;
			for(j=1;j<=i;j++)
			{
				C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
			}
		}
		f[0][0]=1;
		for(i=0;i<MAXN;i++)
		{
			S[0][i]=1;
		}
		for(i=1;i<MAXN;i++)
		{
			f[i][0]=S[i][0]=1;
			for(j=1;j<MAXN;j++)
			{
				f[i][j]=S[i-1][j];
				S[i][j]=(S[i][j-1]+f[i][j])%MOD;
			}
		}
		
		for(i=0;i<=cn&&i<=n;i++)
		{
			for(j=0;j<=cm&&j<=m;j++)
			{
				if((i*m+j*n-2*i*j==s)&&((cn-i)&1^1)&&((cm-j)&1^1))
				{
					(ans+=(ll)C[n][i]*C[m][j]%MOD*f[n][(cn-i)/2]%MOD*f[m][(cm-j)/2]%MOD)%=MOD;
				}
			}
		}
		return (int)ans;
	}
};