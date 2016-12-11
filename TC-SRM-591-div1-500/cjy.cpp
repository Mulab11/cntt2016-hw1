#include<bits/stdc++.h>
using namespace std;
class PyramidSequences
{
	public:
		long long distinctPairs(int n,int m)
		{
			int g=__gcd(--n,--m);
			return 1ll*n/g*m/g*(g-1)+(1ll*(n/g+1)*(m/g+1)+1)/2;
		}
};
