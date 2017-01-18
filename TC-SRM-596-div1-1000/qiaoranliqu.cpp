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
int i,j,m,n,p,k;
long long A[N],Ans[N],sum[N];
void work(int p,int w,int mo)
{
		memset(sum,0,sizeof(sum)); 
		int i;
		for (i=0;i<N;++i) A[i]=(long long)1e18;
		for (i=0;i<=p*w;++i)
		{
				int str=1ll*i*i%p;
				for (;str<mo;str+=p)
				{
						if (sum[str]>=w) continue;
						int now=(str-1ll*i*i%mo+mo)%mo;
						if (!now)  sum[str]+=w;
						else 
						{
								int s=0;
								while (now%p==0) now/=p,++s;
								sum[str]+=s;
						}
						if(sum[str]>=w) A[str]=1ll*i*i;
				}
		}
}
long long cal(long long n,long long p,long long rem)
{
		if (n<rem) return 0;
		return (n-rem)/p+1;
}
class SparseFactorial{
	public:
	long long getCount(long long lo, long long hi, long long divisor)
	{
			for (i=2,j=divisor;i<=j;++i)
				if (j%i==0)
				{
					int a=1,b=0;
					while (j%i==0) a*=i,j/=i,b++;
					work(i,b,a);
					for (k=0;k<divisor;++k)
						Ans[k]=max(Ans[k],A[k%a]);
				}
			long long ans=0;
			for (i=0;i<divisor;++i)
				ans+=cal(hi,divisor,i)-cal(min(hi,max(lo-1,Ans[i])),divisor,i); 
			return ans;
	}
}MRT;

int main()
{
	 cout<<MRT.getCount(1,1000000000000,4);
}

