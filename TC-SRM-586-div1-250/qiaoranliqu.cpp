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
int i,j,m,n,p,k,ans;
int check(vector<int> v,double x)
{
		int i,sum=0;
		for (i=0;i<n-1;++i)
			if (v[i]<v[i+1])
			{
					if (v[i]<=x&&x<v[i+1]) ++sum;
			}
			else 
			{
					 if (x<=v[i]&&v[i+1]<x) ++sum;
			}
		if (v[n-1]==x) ++sum;
		return sum;
}
class PiecewiseLinearFunction{
	public:
		int maximumSolutions(vector <int> Y)
		{
			  n=Y.size();
			  for (i=1;i<n;++i) if (Y[i]==Y[i-1]) return -1;
			  for (i=0;i<n;++i) ans=max(ans,max(check(Y,Y[i]+0.5),max(check(Y,Y[i]),check(Y,Y[i]-0.5))));
			  return ans;
		}
}MRT;

int main()
{
	 cout<<MRT.maximumSolutions({3, 2});
}

