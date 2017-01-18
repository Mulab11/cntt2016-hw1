#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 1000005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
map<int,int>mp;
int i,j,m,n,p[N],k,f[N],g[N];
long long ans;
int prime(int x)
{
		int i;
		for (i=2;i*i<=x;++i)
			if (x%i==0) return 0;
		return 1; 
}
class TheDivisionGame{
	public:
		long long countWinningIntervals(int L, int R)
		{
			n=(int)sqrt(R);
			for (i=2;i<=n;++i) 
				if (prime(i)) p[++p[0]]=i;
			n=R-L+1;
			//sg(n)=w(n) 
			//筛出[L,R]的sg值即可
			for (i=1;i<=n;++i) f[i]=L+i-1;
			for (i=1;i<=p[0];++i)
			{
				int str=(L+p[i]-1)/p[i]*p[i];
				for (;str<=R;str+=p[i])
				{
						while (f[str-L+1]%p[i]==0)
						{
							 g[str-L+1]++;
							 f[str-L+1]/=p[i];
						}
				}
			}
			for (i=1;i<=n;++i) if (f[i]>1) g[i]++;
			mp[0]++; int now=0; ans=1ll*n*(n+1)/2; 
			for (i=1;i<=n;++i)
			{
				 now^=g[i];
				 ans-=mp[now];
				 mp[now]++;
			}
			return ans;
		}
}FFT;

int main()
{
	cout<<FFT.countWinningIntervals(2,100);
}

