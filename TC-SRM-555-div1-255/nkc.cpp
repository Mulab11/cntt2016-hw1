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
#define MAXN 1010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct CuttingBitString
{
	int n;
	char s[MAXN];
	int f[MAXN];
	ll S[MAXN];
	ll mi[MAXN];
	int getmin(string A)
	{
		int i,j;
		memset(f,0x3f,sizeof(f));
		f[0]=0;
		n=A.size();
		for(i=0;i<n;i++)
		{
			s[i+1]=A[i]-'0';
		}
		mi[0]=1;
		for(i=1;i<=n;i++)
		{
			mi[i]=mi[i-1]*2;
			S[i]=S[i-1]*2+s[i];
			for(j=0;j<i;j++)
			{
				if(s[j+1])
				{
					ll t=S[i]-S[j]*mi[i-j];
					while(!(t%5))
					{
						t/=5;
					}
					if(t==1)
					{
						f[i]=min(f[i],f[j]+1);
					}
				}
			}
		}
		return f[n]>INF?-1:f[n];
	}
};