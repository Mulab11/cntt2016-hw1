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
#define MAXN 210
#define MAXM 1010
#define INF 1000000000
#define MOD 1234567891
#define eps 1e-8
#define ll long long
int dn=15;
int N=dn*8;
struct mat
{
	ll x[MAXN][MAXN];
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
					(z.x[i][j]+=x.x[i][k]*y.x[k][j])%=MOD;
				}
			}
		}
		return z;
	}
};
int c,k;
ll h;
int H[1000];
int a[20];
mat A,B,C;
int cald(int *q,int k)
{
	int i,j;
	int t[4];
	int mx=0;
	int re=0;
	int tmp=1000;
	for(i=0;i<4;i++)
	{
		bool flag=1;
		for(j=0;j<i;j++)
		{
			if(q[i]==q[j])
			{
				flag=0;
				t[i]=t[j];
				break;
			}
		}
		if(flag)
		{
			t[i]=mx++;
		}
		re+=tmp*t[i];
		tmp/=10;
	}
	return k*dn+H[re];
}
void dfs(int x,int mx)
{
	int i,j;
	if(x==8)
	{
		ll t=1;
		for(i=4;i<=7;i++)
		{
			bool flag=1;
			for(j=0;j<i;j++)
			{
				if(a[j]==a[i])
				{
					flag=0;
					break;
				}
			}
			if(flag)
			{
				(t*=c-a[i])%=MOD;
			}
		}
		int st=0;
		for(i=0;i<4;i++)
		{
			if(a[i]==a[i+4])
			{
				st++;
			}
		}
		st+=(a[4]==a[5]);
		st+=(a[4]==a[6]);
		st+=(a[7]==a[5]);
		st+=(a[7]==a[6]);
		for(i=st;i<=7;i++)
		{
			(A.x[cald(a,i-st)][cald(a+4,i)]+=t)%=MOD;
		}
		return ;
	}
	for(i=0;i<=mx&&i<c;i++)
	{
		a[x]=i;
		dfs(x+1,max(mx,i+1));
	}
}
struct TheBrickTowerHardDivOne
{
	int find(int _c,int _k,ll _h)
	{
		int i;
		c=_c;
		k=_k;
		h=_h;
		int tmp=0;
		H[123]=tmp++;
		H[12]=tmp++;
		H[102]=tmp++;
		H[121]=tmp++;
		H[122]=tmp++;
		H[120]=tmp++;
		H[112]=tmp++;
		H[11]=tmp++;
		H[101]=tmp++;
		H[110]=tmp++;
		H[111]=tmp++;
		H[100]=tmp++;
		H[1]=tmp++;
		H[10]=tmp++;
		H[0]=tmp++;
		dfs(0,0);
		for(i=0;i<=N;i++)
		{
			B.x[i][i]=1;
		}
		C.x[0][0]=(ll)c*(c-1)%MOD*(c-2)%MOD*(c-3)%MOD;
		C.x[0][dn+1]=(ll)c*(c-1)%MOD*(c-2)%MOD;
		C.x[0][dn+2]=(ll)c*(c-1)%MOD*(c-2)%MOD;
		C.x[0][dn+3]=(ll)c*(c-1)%MOD*(c-2)%MOD;
		C.x[0][dn+4]=(ll)c*(c-1)%MOD*(c-2)%MOD;
		C.x[0][5]=(ll)c*(c-1)%MOD*(c-2)%MOD;
		C.x[0][6]=(ll)c*(c-1)%MOD*(c-2)%MOD;
		C.x[0][dn*2+7]=(ll)c*(c-1)%MOD;
		C.x[0][dn*2+8]=(ll)c*(c-1)%MOD;
		C.x[0][9]=(ll)c*(c-1)%MOD;
		C.x[0][dn*2+10]=(ll)c*(c-1)%MOD;
		C.x[0][dn*2+11]=(ll)c*(c-1)%MOD;
		C.x[0][dn*2+12]=(ll)c*(c-1)%MOD;
		C.x[0][dn*2+13]=(ll)c*(c-1)%MOD;
		C.x[0][dn*4+14]=c;
		for(i=0;i<(k+1)*dn;i++)
		{
			A.x[i][N]=1;
		}
		A.x[N][N]=1;
		while(h)
		{
			if(h&1)
			{
				B=B*A;
			}
			A=A*A;
			h>>=1;
		}
		C=C*B;
		return C.x[0][N];
	}
};