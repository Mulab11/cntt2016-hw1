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

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
long long ans;
long long cal(int x)
{
		long long s=0;
		for (i=0;i<=x;++i) s+=(x-i+1);
		return s;
}
class AlternateColors2{
		public:
			long long countWays(int n, int k)
			{
				//the last round before k-th is rgb
				if ((k-1)%3==0) ans+=cal(n-k);
				//the last round before k-th is rg or rb
				for (i=0;i<=n;++i)
					if (3*i<k)
					{
							int rest=k-1-3*i;
							if (rest&1) continue;
							if (rest==0) continue;
							ans+=(n-k+1)*2;	
					}
				//the last round before k-th is r 
				for (i=0;i<k-1;++i) // the number of rgb....rg/rb.... is i
				{						//3*x+2*y=i; x>=0 y>=0 x=(i-2*y)/3;
						int str=0,end=i/2;
						while ((i-2*end)%3!=0) --end;
						if (i%3==0) str=0; 
						else if (i%3==1) str=2;
						else str=1;
						if (str>end) continue;			
						ans+=(end-str+3)/3*2;
						if (i%3==0) --ans;
				}
				return ans;
			}
}E;

int main()
{
	cout<<E.countWays(6,4);
}
