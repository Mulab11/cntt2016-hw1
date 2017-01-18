#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
class FoxPaintingBalls{
	public:
	long long theMax(long long R, long long G, long long B, int N)
	{
		  long long sum=1ll*N*(N+1)/2;
		  if (sum==1) return G+B+R;  
		  if (sum%3==0)//三种都一样. 
		  {
		  		sum/=3;
		  		return min(R/sum,min(G/sum,B/sum));
		  }
		  else 
		  {
		  		sum/=3; //每个都有种多一个 
		  		long long l=0,r=max(R/sum,max(G/sum,B/sum))+1,mid=0;
		  		while ((l+r)>>1!=mid) 
				{
						mid=(l+r)>>1;
						if (sum*mid>min(R,min(G,B))) r=mid;
						else if (R+G+B-sum*mid*3>=mid) l=mid;
						else r=mid;
				}
				return l;
		  }
	}
};
