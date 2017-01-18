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
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
int gcd(int x,int y)
{
	 return !y?x:gcd(y,x%y);
}
class PyramidSequences
{
	 public:
	 	long long distinctPairs(int n,int m)
	 	{
	 		  long long g=gcd(--n,--m),x=n/g,y=m/g;
	 		  return (g-1)*x*y+(x+1)*(y+1)/2;
	 	}
};
