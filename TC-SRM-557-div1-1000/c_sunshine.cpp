#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;

class XorAndSum
{
	public:
	int n;
	LL x[55];
	void gauss()
	{
		int i=0,j;
		for(LL k=1LL<<60;k&&i<n;k>>=1)
		{
			for(j=i+1;j<=n;j++)
				if(x[j]&k)break;
			if(j>n)continue;
			i++;
			swap(x[i],x[j]);
			for(j=1;j<=n;j++)
				if(j!=i&&x[j]&k)x[j]^=x[i];
		}
	}
	LL maxSum(vector<LL> number)
	{
		n=number.size();
		for(int i=1;i<=n;i++)
			x[i]=number[i-1];
		//We use Gaussian elimination to determine the set of basis vectors.
		gauss();
		//We can prove S that is the xor-sum of the set of basis vectors is the maximum number we can get.
		for(int i=2;i<=n;i++)
			x[1]^=x[i];
		//Let x[1] equal S, and for 1<i<=n we turn x[i] to x[i] xor S to get the maximum sum.
		LL res=x[1];
		for(int i=2;i<=n;i++)
			x[i]^=x[1],res+=x[i];
		return res;
	}
};

