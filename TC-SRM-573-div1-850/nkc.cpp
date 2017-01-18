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
#define MAXM 300010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct WolfPack
{
	int X[MAXN],Y[MAXN];
	ll fac[MAXM],ine[MAXM];
	ll ansx,ansy;
	int n,m;
	ll C(int x,int y)
	{
		return fac[x]*ine[y]%MOD*ine[x-y]%MOD;
	}
	ll cal(int *p,int t)
	{
		int i;
		ll re=1;
		for(i=1;i<=n;i++)
		{
			if(((m-abs(p[i]-t))&1)||abs(p[i]-t)>m)
			{
				return 0;
			}
			(re*=C(m,(m-abs(p[i]-t))/2))%=MOD;
			if(!re)
			{
				return 0;
			}
		}
		return re;
	}
	int calc(vector<int> _X,vector<int> _Y,int _m)
	{
		int i;
		n=_X.size();
		m=_m;
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
		for(i=1;i<=n;i++)
		{
			X[i]=_X[i-1]-_Y[i-1];
			Y[i]=_X[i-1]+_Y[i-1];
		}
		for(i=-300000;i<=300000;i++)
		{
			(ansx+=cal(X,i))%=MOD;
			(ansy+=cal(Y,i))%=MOD;
		}
		return ansx*ansy%MOD;
	}
};