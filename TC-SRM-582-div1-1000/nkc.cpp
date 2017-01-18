#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cmath>
#define N 431000
#define M 17000
#define eps 1e-12
using namespace std;
bool num[N];
vector<int>V[N],f[N];
bool psqr[N],pcub[M];
int *ones=new int[N];
struct SemiPerfectPower
{
	long long sqr(long long x)
	{return x*x;}
	long long cub(long long x)
	{return x*x*x;}
	long long qua(long long x)
	{return x*x*x*x;}
	long long gcd(long long a,long long b)
	{
		if(a==0) return b;
		return gcd(b%a,a);
	}
	inline int floor_sqrt(const long long &n)
	{
		int le = 1, ri = 282842713;
		while (le != ri)
		{
			int mid = (le + ri) >> 1;
			if ((long long)mid * mid <= n)
				le = mid + 1;
			else
				ri = mid;
		}
		return le - 1;
	}
	inline int floor_cubert(const long long &n)
	{
		int le = 1, ri = N + 1;
		while (le != ri)
		{
			int mid = (le + ri) >> 1;
			if ((long long)mid * mid * mid <= n)
				le = mid + 1;
			else
				ri = mid;
		}
		return le - 1;
	}
	void predo()
	{
		int i,j;
		for(i=2;sqr(i)<N;i++)
		for(j=1;j*sqr(i)<N;j++)
		psqr[j*sqr(i)]=true;
		for(i=2;cub(i)<M;i++)
		for(j=1;j*cub(i)<M;j++)
		pcub[j*cub(i)]=true;
		for(i=1;i<=N;i++) num[i]=1;
		for(i=1;i<N;i++)
		if(!psqr[i])
		{
			if(i==1) num[i]=0;
			for(j=1;i*j<N;j++)
			{
				if(j<=i) num[i*j]=num[i]^num[j];
				if(j!=1) ones[i*j]=i;
			}
		}
		for(i=1;i<M;i++)
		if(!psqr[i])
		{
			f[i].push_back(0);
			for(j=1;i*j<N;j++)
			f[i].push_back(f[i][j-1]+(!psqr[i*j]));
		}
		for(i=1;i<N;i++)
		if(!psqr[i])
		{
			j=i;
			while(j!=1)
			V[i].push_back(j/ones[j]),j=ones[j];
		}
		delete[] ones;
	}
	long long cal(long long X)
	{
		long long i,j,k,x,y,a,b;
		long long ret=0;
		for(i=1;cub(i)<=X;i++)
		if(!psqr[i])
		ret+=floor_sqrt(X/i)-i;
		cout<<ret<<endl;
		for(x=1;qua(x)<=X;x++)
		if(!pcub[x])
		{
			for(k=1;cub(k)<=x;k++)
			{
				y=k*k/gcd(x,k*k);
				a=x*y/(k*k);
				if(psqr[a]) continue;
				long long pmin=x/y+1,pmax=floor_cubert(X/x)/y;
				if(pmin>pmax) continue;
				for(j=0;j<(1<<V[a].size());j++)
				{
					long long d=1;
					for(i=0;i<V[a].size();i++)
					if(j&(1<<i))
					d*=V[a][i];
					if(num[d]) ret-=f[d][pmax/d]-f[d][(pmin-1)/d];
					else ret+=f[d][pmax/d]-f[d][(pmin-1)/d];
				}
			}
		}
		return ret;
	}
	long long count(long long L, long long R)
	{
		predo();
		return cal(R)-cal(L-1);
	}
};
/*SemiPerfectPower P;
int main()
{
	vector<string> V;
	long long l,r;
//	cin>>l>>r;
	//cout<<P.count(432,432);
	cout<<P.count(80000000000000000LL,80000000000000000LL);
}*/