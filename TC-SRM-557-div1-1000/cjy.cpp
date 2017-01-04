#include<bits/stdc++.h>
using namespace std;
int i,j,k=62,n;
long long s;
class XorAndSum
{
	public:
		int n;
		long long maxSum(vector<long long> a)
		{
			for(n=a.size();~k;k--)
			{
				for(j=i;j<n&&!(a[j]>>k&1);j++);
				if(j==n)continue;
				for(swap(a[i],a[j]),j=0;j<n;j++)if(j!=i&&a[j]>>k&1)a[j]^=a[i];i++;
			}
			for(i=1;i<n;i++)a[0]^=a[i];
			for(i=1;i<n;i++)s+=a[i]^a[0];
			return s+a[0];
		}
};
