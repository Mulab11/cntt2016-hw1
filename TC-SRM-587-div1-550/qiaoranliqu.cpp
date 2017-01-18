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
int i,j,m,n,p,k,W;
double work(int y)
{
		if (y==0) return 0;
		return 1./W/(1./W+1./y);
}
class TriangleXor{
	public:
	int theArea(int W)
	{
			::W=W;
			double ans=0.;
			for (i=0;i<=W;++i)
			{
					int ge=W+1-i,up=0;
					if (i==0) up=1; 
					else if (i&1) up=-2;
					else up=2;
					ans+=ge*up*(1.-work(i))*W/2.;
			}
			return (int)ans;
	}
}MRT;

int main()
{
	 cout<<MRT.theArea(2);
}
