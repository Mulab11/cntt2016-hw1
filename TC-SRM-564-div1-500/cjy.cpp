#include<bits/stdc++.h>
using namespace std;
long long s,i;
class AlternateColors2
{
	public:
		long long countWays(int n,int k)
		{
			if(k%3==1)s+=1ll*(n-k+1)*(n-k+2)/2;
			for(;i<(k+1)/3;i++)s+=(k-i*3)%2?n*2-i*3-k:k-i*3-1;
			return s;
		}
};
